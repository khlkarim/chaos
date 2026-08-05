#define SHARED_IMPLEMENTATION
#include "shared.h"

#include <memory>
#include <string>
#include "materials/Lambertian.h"

constexpr const char *OUTPUT_FILE_PATH = "./cube-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(RENDERER_SAMPLES_PER_PIXEL);
  renderer.setMaxDepth(RENDERER_MAX_DEPTH);

  init(scene);
  renderer.render(scene);
  IO::save(renderer, OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}

void init(Scene &scene) {
  auto &camera = scene.getCamera();
  auto &em = scene.getEntityManager();
  init(camera);

  auto material = std::make_shared<Lambertian>(COLOR_GREY);
  auto transform = std::make_shared<Transform>(Vec3(-0.5, -0.5, -0.5));
  drawCube(scene, {transform, material});
}

void init(Camera &camera) {
  camera.setPitch(-30);
  camera.setPosition(Vec3(0, 1, 2));
}
