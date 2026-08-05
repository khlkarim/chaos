cmake_minimum_required(VERSION 3.20)
project(chaos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TESTS
  ray
  crt
  cube
  chaos
  model
  light
  entity
  sphere
  fractal
  cornell
  texture
  triangle
)

set(SOURCES
  ./src/entity/Entity.cpp

  ./src/components/Metadata.cpp
  ./src/components/Hierarchy.cpp
  ./src/components/Transform.cpp
  ./src/components/Geometry.cpp
  ./src/components/Material.cpp

  ./src/materials/Metal.cpp
  ./src/materials/Emissive.cpp
  ./src/materials/Dielectric.cpp
  ./src/materials/Lambertian.cpp

  ./src/geometry/Ray.cpp
  ./src/geometry/Mesh.cpp
  ./src/geometry/Quad.cpp
  ./src/geometry/Sphere.cpp
  ./src/geometry/Vector.cpp
  ./src/geometry/Circle.cpp
  ./src/geometry/Rectangle.cpp
  ./src/geometry/Intersection.cpp

  ./src/renderer/Scene.cpp
  ./src/renderer/Camera.cpp
  ./src/renderer/Renderer.cpp

  ./src/skybox/Sky.cpp
  ./src/skybox/Monochrome.cpp

  ./src/textures/Image.cpp
  ./src/textures/SolidColor.cpp
  ./src/textures/CheckerBoard.cpp

  ./src/io/IO.cpp
  ./src/io/CRT.cpp
  ./src/io/OBJ.cpp
  ./src/io/PPM.cpp

  ./src/utils/math.cpp
  ./src/utils/string.cpp
  ./src/utils/stb_image.cpp
  ./src/utils/stb_image_write.cpp
)

function(build_test test)
  add_executable(${test})
  target_sources(${test} PRIVATE ./test/${test}.cpp ${SOURCES})
  target_include_directories(${test} PRIVATE ./include ./test)
endfunction()

foreach(item IN LISTS TESTS)
  build_test(${item})
endforeach()
