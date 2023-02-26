#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

class Window
{

public:
    bool framebufferResized = false;

    void destroy();

    void handleMinimization();

    void getFramebufferSize(int* width, int* height);

    int shouldClose() { return glfwWindowShouldClose(r_window); }

    void poll() { glfwPollEvents(); }

    GLFWwindow* getWindow() { return r_window; }

    VkResult createSurface(VkInstance instance, VkSurfaceKHR* surface, VkAllocationCallbacks* allocationCallbacks=nullptr);

    void createWindow(uint32_t w = 800, uint32_t h = 600);

private:
    GLFWwindow* r_window;

    uint32_t m_width, m_height;
    
    // HELPERS

        // Used by createWindow();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};