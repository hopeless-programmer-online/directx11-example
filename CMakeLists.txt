cmake_minimum_required(VERSION 3.25)
project(directx11_example)

add_executable(example
    "src/main.cpp"
)
target_compile_features(example PUBLIC cxx_std_17)
