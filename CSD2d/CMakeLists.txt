set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
cmake_minimum_required(VERSION 3.20)
project(MyProject LANGUAGES CXX)

add_subdirectory(JUCE)
add_subdirectory(p1)
