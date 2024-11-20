#pragma once

#include "Modules/Renderer/Renderer.h"


//#include <iostream>

int main() {
    Renderer renderer;
    Window windowRef;

    try {
        renderer.window = windowRef;
        renderer.window.createWindow(1980, 1080);
        renderer.customModelLoader = false;
        renderer.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}