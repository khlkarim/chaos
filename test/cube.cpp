#include <memory>
#include <string>

#include "io/IO.h"
#include "materials/Lambertian.h"

constexpr int IMAGE_WIDTH = 640;
constexpr int IMAGE_HEIGHT = 360;
constexpr const char *INPUT_FILE_PATH = "./assets/cube.obj";
constexpr IO::FileFormat INPUT_FILE_FORMAT = IO::FileFormat::OBJ;
constexpr const char *OUTPUT_FILE_PATH = "./cube-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);
EntityId loadModel(EntityManager &em, const std::string &path);

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
  loadModel(em, INPUT_FILE_PATH);
}

void init(Camera &camera) {
  camera.setPitch(-30);
  camera.setPosition(Vec3(0, 1, 2));
}

EntityId loadModel(EntityManager &em, const std::string &path) {
  auto model = em.createEntity();

  auto material = std::make_shared<Lambertian>(COLOR_GREY);
  auto mesh = std::make_shared<Mesh>();
  auto transform = std::make_shared<Transform>(Vec3(-0.5, -0.5, -0.5));

  IO::load(*mesh, INPUT_FILE_PATH, IO::FileFormat::OBJ);
  em.setAll(model, {mesh, material, transform});

  return model;
}
