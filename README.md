# Vulkan Starter

The long-term goal of this project is to create a template for future graphics apps I want to make. Why am I using Vulkan? I hate myself and I want to suffer. No but really its because I like tinkering with things and I do that best when I'm writing bad code at my home computer. 1000 lines to draw a triangle? I'm salivating already. 
## **Goals**

**Brief:**  
- Gain a deep understanding of Graphics pipelines, GPU operation, memory management, and the Vulkan API
- Create a template Vulkan project that I can use as a starter for future graphics applications.

## **How Vulkan Works**
This section is my equavalent to study notes. I go through every part of the starter triangle program and try to gain a deeper understanding of the Vulkan stuff going on. Welcome to the hellscape that is my mind.
### **Overview**

```cpp
    // INITIALIZING VULKAN INSTANCE
    void initVulkan() {
        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createCommandBuffer();
        createSyncObjects();
    }
```

The above `initVulkan()` function does what it says: it initializes Vulkan. In order to use Vulkan, an instance of the API must be created. This is an involved processes as you can see from the unholy number of functions. We'll go through them one by one. God forbid you get lost so hold my hand.

### **1. Instances and Debugging**

We start at the start with `createInstance()`
```cpp
    void initVulkan() {
        createInstance(); 
        ...
    }

```
It's time, my friends, for a trial by fire. When they say Vulkan is verbose, they mean it. Below I've provided the full function code but fear not friend, we're going through it line by line. I'm simply providing the full code for context so you can come back to it and see how the different parts click together. 

```cpp
 // INSTANCE CREATION
    void createInstance() {
        // A lot of information is passed through structs rather than function parameters
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested but not available...");
        }
        
        // optional but helpful information for the driver
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;
        
        // MANDATORY for instance creation
        // Telling Vulkan what global (program) extensions and validations we want to use
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;


        // ADDING appInfo to createInfo
        createInfo.pApplicationInfo = &appInfo;


        // Vulkan is platform agnostic. Here we provide the GLFW extension to interface with the window system
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }


    }
```

### **Validation Layers**

The first step to coding in Vulkan is to make sure you don't fuck it up. Vulkan allows you to debug your code through the usage of <ins>*Validation Layers*</ins>. A Validation Layer is code that checks your code. Vulkan provides extensive debug utility with this layer as opposed to OpenGL. In OpenGL, debugging is very limited and running constantly in the background. In Vulkan, however, debugging code is specified in the Validation Layer which can be toggled on or off depending on your build (debug or release). 

Advantage: Lighter release versions since debug code can be disabled.

Disadvantage: You write the debug code.

```cpp
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
...
    void createInstance() {
        ...
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested but not available...");
        }
        ...
    }
...
```

Toggling the validation layer depends on the `enableValidationLayers` variable. The `ifdef` at the top of our file determines this value based on whether our code is running in debug mode or not with the `NDEBUG` variable. 

Thankfully, we don't have to write that much custom code since Khronos provide us with their own debugging in `VK_LAYER_KHRONOS_validation`. For now, we create the `validationLayers` struct and put that in there. Now that we defined what type of validation layer we have to check if its available. This is done in `checkValidationLayerSupport()`

```cpp
    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }
```

To understand what's happening in the code above, I've pasted the Vulkan spec for `vkEnumerateInstanceLayerProperties`. 

```cpp
VkResult vkEnumerateInstanceLayerProperties(
    uint32_t*           pPropertyCount,
    VkLayerProperties*  pProperties);
```

According to the Vulkan spec:

If pProperties is `NULL`, then the number of layer properties available is returned in `pPropertyCount`. Otherwise, `pPropertyCount` must point to a variable set by the user to the number of elements in the `pProperties` array, and on return the variable is overwritten with the number of structures actually written to `pProperties`. If `pPropertyCount` is less than the number of layer properties available, at most `pPropertyCount` structures will be written, and `VK_INCOMPLETE` will be returned instead of `VK_SUCCESS`, to indicate that not all the available properties were returned.

With that, I'll explain what's happening in the following code snippet:

```cpp
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
```

The first call to `vkEnumerateInstanceLayerProperties` has `nullptr` passed to it and so the number of layer properties available is returned in our variable `layerCount`

Before the second call we declare a vector of size `layerCount` named `availableLayers`. The second call will then write at most `layerCount` structures to `availableLayers`

Now that we have the list of available layers, we can check if our `VK_LAYER_KHRONOS_validation` is among them. Or us, even. Among Us, even.
```cpp
        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
```
We loop through the `validationLayers` struct we specified earlier, for each member of that struct (we only have one at this point) we check the list of available layers. If we find it, we're golden, return true. If we don't, we have failed. It's over. No validation layer for you. Do not pass go. So disappointing. 

There is a lot of other debugging code here, namely the debug callbacks but dear god I don't care. I just care that it works. Go to https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Validation_layers if you want to learn about that. 

Now it's time to go through the rest of the `createInstance()` function.

```cpp
// optional but helpful information for the driver
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;
        // MANDATORY for instance creation
        // Telling Vulkan what global (program) extensions and validations we want to use
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;


        // ADDING appInfo to createInfo
        createInfo.pApplicationInfo = &appInfo;
```
Here we populate the `pApplicationInfo` member of the `VkInstanceCreateInfo` struct `createInfo`. I'll let the Vulkan spec explain the relevance of this:

- `pApplicationInfo` is `NULL` or a pointer to a `VkApplicationInfo` structure. If not `NULL`, this
information helps implementations recognize behavior inherent to classes of applications. (pg.100)


```cpp
        // Vulkan is platform agnostic. Here we provide the GLFW extension to interface with the window system
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
```
Before creating an instance of Vulkan we need to pass it extension and layer information. We've created a validation layer so we need to inform Vulkan whether we have enabled or disabled it as well as bringing in any GLFW extensions we need. The code for this part is done in `getRequiredExtensions`. 

After all this information has been collected into the `createInfo` struct, we can make a call to `vkCreateInstance()` and create the Vulkan instance. Congratulations, we can now use Vulkan. Sort of hahahahaahahaHAHAHAHAHahahaahHahaHAHaha **welcome to hell.**

## **2. Surfaces**
```cpp
    void initVulkan() {
        createInstance();
        setupDebugMessenger();
        createSurface(); // WE ARE HERE
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createCommandBuffer();
        createSyncObjects();
    }
```

First thing we gotta do is create a variable to store the surface. This variable is of type `VkSurfaceKHR`. We do this at the top of the HelloTriangleApp class. 

## **Progress Report**

### Date: February 17, 2023

At first I saw nothing, now,  <b>*triangle*</b>.

![image](https://user-images.githubusercontent.com/33097098/219802681-8ceb1f40-cd0a-4ce3-a6a2-a239e98a4b15.png)

It watches.

### Date: February 19, 2023

No longer hardcoding vertex data. Using vertex buffers. 

![image](https://user-images.githubusercontent.com/33097098/219983754-3c6202aa-81fc-4629-b666-79c5d4850d0d.png)


