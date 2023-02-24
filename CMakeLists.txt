cmake_minimum_required(VERSION 3.25)
project(directx11_example)

include(FetchContent)

FetchContent_Declare(glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG        "3.3.8"
)
FetchContent_MakeAvailable(glfw)

add_executable(example
    "src/main.cpp"
)
target_compile_features(example PUBLIC
    cxx_std_17
)
target_link_libraries(example PUBLIC
    glfw
)
