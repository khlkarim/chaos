#include <memory>

#include "io/IO.h"
#include "geometry/Sphere.h"
#include "materials/Metal.h"
#include "materials/Dielectric.h"
#include "materials/Lambertian.h"

constexpr int IMAGE_WIDTH = 320;
constexpr int IMAGE_HEIGHT = 180;
constexpr const char *OUTPUT_FILE_PATH = "sphere-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);
EntityId drawSphere(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat);

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(5);

  init(scene);
  renderer.render(scene);
  IO::save(renderer, OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}

void init(Scene &scene) {
  Camera &camera = scene.getCamera();
  EntityManager &em = scene.getEntityManager();
  init(camera);

  auto centerMat = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5, 1.0));
  auto centerTransform = std::make_shared<Transform>(Vec3(0, 0, -1.2), Vec3(1));
  drawSphere(em, centerTransform, centerMat);

  auto groundMat = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0, 1.0));
  auto groundTransform = std::make_shared<Transform>(Vec3(0, -101, -1), Vec3(100));
  drawSphere(em, groundTransform, groundMat);

  auto rightMat = std::make_shared<Metal>(Color(0.8, 0.6, 0.2, 1.0), 1.0);
  auto rightTransform = std::make_shared<Transform>(Vec3(2, 0, -1), Vec3(1));
  drawSphere(em, rightTransform, rightMat);

  auto leftMat = std::make_shared<Dielectric>(1.5);
  auto leftTransform = std::make_shared<Transform>(Vec3(-2, 0, -1), Vec3(1));
  drawSphere(em, leftTransform, leftMat);

  auto bubbleMat = std::make_shared<Dielectric>(1 / 1.5);
  auto bubbleTransform = std::make_shared<Transform>(Vec3(-2, 0, -1), Vec3(0.8));
  drawSphere(em, bubbleTransform, bubbleMat);
}

void init(Camera &camera) { camera.setPosition(Vec3(0, 0, 1)); }

EntityId drawSphere(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat) {
  auto s = em.createEntity();

  float radius = transform->getScale().x;
  auto sdf = std::make_shared<Sphere>(radius);
  em.setAll(s, {mat, sdf, transform});

  return s;
}
