#include <iostream>
#include <stdexcept>
#include <vector>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>
#include <d3d11.h>
#include <dxgi.h>

auto main(const int argn, const char* argv[]) -> int
{
    try
    {
        if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW.");

        auto window = glfwCreateWindow(512, 512, "Window", NULL, NULL);

        if (!window) throw std::runtime_error("Failed to create a window.");

        int width;
        int height;
        {
            glfwGetWindowSize(window, &width, &height);
        }

        ID3D11Device* device;
        ID3D11DeviceContext* context;
        IDXGISwapChain* swapChain;
        {
            DXGI_SWAP_CHAIN_DESC swapChainDescription = {
                .BufferDesc   = {
                    .Width            = static_cast<UINT>(width),
                    .Height           = static_cast<UINT>(height),
                    .RefreshRate      = { 0, 1 },
                    .Format           = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
                    .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
                    .Scaling          = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED,
                },
                .SampleDesc   = {
                    .Count   = 1,
                    .Quality = 0,
                },
                .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
                .BufferCount  = 3,
                .OutputWindow = glfwGetWin32Window(window),
                .Windowed     = FALSE,
                .SwapEffect   = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD,
                .Flags        = 0,
            };
            std::vector<D3D_FEATURE_LEVEL> features = {
                D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0,
            };

            if (FAILED(D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG,
                features.data(), features.size(),
                D3D11_SDK_VERSION,
                &swapChainDescription,
                &swapChain,
                &device,
                nullptr,
                &context
            ))) throw std::runtime_error("Failed to create DirectX11 context.");
        }

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
