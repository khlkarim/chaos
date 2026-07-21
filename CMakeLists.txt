cmake_minimum_required(VERSION 3.20)
project(chaos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TESTS
  fractal
  ray
  model
  sphere
  triangle
)

set(SOURCES
  ./src/geometry/Circle.cpp
  ./src/geometry/Mesh.cpp
  ./src/geometry/Ray.cpp
  ./src/geometry/Rectangle.cpp
  ./src/geometry/Sphere.cpp
  ./src/geometry/Vector.cpp

  ./src/renderer/Camera.cpp
  ./src/renderer/Renderer.cpp
  ./src/renderer/Scene.cpp

  ./src/utils/math.cpp
  ./src/utils/AssetLoader.cpp
  ./src/utils/stb_image_write.cpp
)

function(build_test test)
  add_executable(${test})
  target_sources(${test} PRIVATE ./test/${test}.cpp ${SOURCES})
  target_include_directories(${test} PRIVATE ./include)
endfunction()

foreach(item IN LISTS TESTS)
  build_test(${item})
endforeach()
