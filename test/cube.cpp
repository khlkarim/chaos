#include <memory>
#include <string>

#include "io/IO.h"
#include "materials/Lambertian.h"

constexpr int IMAGE_WIDTH = 320;
constexpr int IMAGE_HEIGHT = 180;
constexpr const char *CUBE_FILE_PATH = "./assets/cube.obj";
constexpr IO::FileFormat CUBE_FILE_FORMAT = IO::FileFormat::OBJ;
constexpr const char *OUTPUT_FILE_PATH = "./cube-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);
EntityId drawCube(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> material);

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(5);

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
  drawCube(em, transform, material);
}

void init(Camera &camera) {
  camera.setPitch(-30);
  camera.setPosition(Vec3(0, 1, 2));
}

EntityId drawCube(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> material) {
  auto model = em.createEntity();

  auto mesh = std::make_shared<Mesh>();
  IO::load(*mesh, CUBE_FILE_PATH, CUBE_FILE_FORMAT);
  em.setAll(model, {mesh, material, transform});

  return model;
}
