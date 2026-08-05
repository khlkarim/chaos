#define SHARED_IMPLEMENTATION
#include "shared.h"

#include <memory>
#include "materials/Lambertian.h"

constexpr const char *OUTPUT_FILE_PATH = "texture-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;
constexpr const char *TEXTURE_FILE_PATH = "./assets/textures/earth.jpg";
constexpr IO::FileFormat TEXTURE_FILE_FORMAT = IO::FileFormat::JPEG;

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
  Camera &camera = scene.getCamera();
  EntityManager &em = scene.getEntityManager();
  init(camera);

  Image image;
  IO::load(image, TEXTURE_FILE_PATH, TEXTURE_FILE_FORMAT);

  auto mat = std::make_shared<Lambertian>(std::make_shared<Image>(image));
  auto transform = std::make_shared<Transform>(Vec3(0, 0, 0), Vec3(1));
  drawSphere(scene, {transform, mat});
}

void init(Camera &camera) {
  camera.setFov(20);
  camera.setPosition(Vec3(0, 0, 5));
}
