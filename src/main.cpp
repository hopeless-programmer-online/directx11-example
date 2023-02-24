#include <iostream>
#include <stdexcept>
#include <glfw/glfw3.h>

auto main(const int argn, const char* argv[]) -> int
{
    try
    {
        if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW.");

        auto window = glfwCreateWindow(512, 512, "Window", NULL, NULL);

        if (!window) throw std::runtime_error("Failed to create a window.");

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }

        glfwTerminate();
    }
    catch(std::runtime_error error)
    {
        std::cerr << error.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "Unknown exception." << std::endl;
    }

    std::cout << "done" << std::endl;

    return 0;
}
