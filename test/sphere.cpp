#include <memory>

#include "io/IO.h"
#include "geometry/Sphere.h"
#include "materials/Metal.h"
#include "materials/Lambertian.h"

constexpr int IMAGE_WIDTH = 640;
constexpr int IMAGE_HEIGHT = 360;
constexpr const char *OUTPUT_FILE_PATH = "sphere-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);
EntityId createSphere(EntityManager &em, Vec3 center, float radius, std::shared_ptr<Material> mat);

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

  auto lambertian = std::make_shared<Lambertian>(COLOR_GREY);
  auto metal1 = std::make_shared<Metal>(COLOR_GREY);
  auto metal2 = std::make_shared<Metal>(COLOR_GREY);

  createSphere(em, Vec3(0, 0, -1), 1, lambertian);
  createSphere(em, Vec3(-2.5, 0, -1), 1, metal1);
  createSphere(em, Vec3(2.5, 0, -1), 1, metal2);
  createSphere(em, Vec3(0, -101, -1), 100, lambertian);
}

void init(Camera &camera) { camera.setPosition(Vec3(0, 0, 1)); }

EntityId createSphere(EntityManager &em, Vec3 center, float radius, std::shared_ptr<Material> mat) {
  auto s = em.createEntity();

  auto transform = std::make_shared<Transform>(center);
  auto sdf = std::make_shared<Sphere>(radius);
  em.setAll(s, {mat, sdf, transform});

  return s;
}
