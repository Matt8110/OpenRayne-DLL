cmake_minimum_required(VERSION 2.8)

set(CMAKE_CROSSCOMPILING_EMULATOR "wine")
set(CMAKE_C_COMPILER "/usr/bin/i686-w64-mingw32-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/i686-w64-mingw32-g++")

project(OpenRayne)

file(GLOB OpenRayne_SRC
     "*.h"
     "*.cpp"
     "engine/*.h"
     "engine/*.cpp"
     "core/*.h"
     "core/*.cpp"
)

add_executable(OpenRayne ${OpenRayne_SRC})
