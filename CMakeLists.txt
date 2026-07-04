cmake_minimum_required(VERSION 3.20)
project(chaos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(fractal)

target_sources(fractal PRIVATE
  ./test/fractal.cpp
  ./src/geometry/Circle.cpp
  ./src/geometry/Rectangle.cpp
  ./src/geometry/Vector.cpp
  ./src/renderer/Renderer.cpp
)

target_include_directories(fractal PRIVATE
  ./include
)
