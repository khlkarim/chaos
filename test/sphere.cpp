#include <memory>

#include "geometry/Sphere.h"
#include "renderer/Camera.h"
#include "renderer/Renderer.h"

constexpr int IMAGE_WIDTH = 1280;
constexpr int IMAGE_HEIGHT = 720;
constexpr FileFormat OUTPUT_FILE_FORMAT = PNG;
constexpr const char *OUTPUT_FILE_PATH = "sphere-output-01.png";

int main() {
  Scene scene;
  Camera &camera = scene.getCamera();
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  camera.setPosition(Vec3(0, 0, 1));

  auto s1 = std::make_shared<Sphere>(1, Vec3(0, 0, -1));
  auto s2 = std::make_shared<Sphere>(100, Vec3(0, -101, -1));
  scene.entities.push_back(s1);
  scene.entities.push_back(s2);

  renderer.render(scene);
  renderer.write(OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}
