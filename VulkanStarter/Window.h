#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// GLFW WINDOW CREATION
void createWindow() {

    // GLFW creates an OpenGL context so we need to undo that
    glfwInit();

    // Undoing OpenGL context creation
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    // Very important line, if you forget this then the callback with cause an access violation due to nullptr
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

// Checks if the framebuffer has been resized using GLFW function
static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    // glfwWindowUserPointer returns a reference to our app, so we cast it to HelloTriangleApplication then set that app object's 
    // framebufferResized variable to true
    auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}



class Window
{
public:
    void createWindow();

private:
    GLFWwindow* window;
};