#define SHARED_IMPLEMENTATION
#include "shared.h"

#include <memory>
#include "materials/Metal.h"
#include "materials/Dielectric.h"
#include "materials/Lambertian.h"

constexpr const char *OUTPUT_FILE_PATH = "sphere-output-01.png";
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
  Camera &camera = scene.getCamera();
  EntityManager &em = scene.getEntityManager();
  init(camera);

  auto groundTransform = std::make_shared<Transform>(Vec3(0, -101, -1), 100);
  auto groundMat = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0, 1.0));
  drawSphere(scene, {groundTransform, groundMat});

  auto centerTransform = std::make_shared<Transform>(Vec3(0, 0, -1.2), 1);
  auto centerMat = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5, 1.0));
  drawSphere(scene, {centerTransform, centerMat});

  auto rightTransform = std::make_shared<Transform>(Vec3(2, 0, -1), 1);
  auto rightMat = std::make_shared<Metal>(Color(0.8, 0.6, 0.2, 1.0), 1.0);
  drawSphere(scene, {rightTransform, rightMat});

  auto leftMat = std::make_shared<Dielectric>(1.5);
  auto leftTransform = std::make_shared<Transform>(Vec3(-2, 0, -1), 1);
  drawSphere(scene, {leftTransform, leftMat});

  auto bubbleMat = std::make_shared<Dielectric>(1 / 1.5);
  auto bubbleTransform = std::make_shared<Transform>(Vec3(-2, 0, -1), 0.8);
  drawSphere(scene, {bubbleTransform, bubbleMat});
}

void init(Camera &camera) { camera.setPosition(Vec3(0, 0, 1)); }
