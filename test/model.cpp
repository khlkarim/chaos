#include <cmath>
#include <memory>
#include <string>
#include <iostream>

#include "io/IO.h"
#include "utils/math.h"
#include "materials/Lambertian.h"

constexpr int IMAGE_WIDTH = 640;
constexpr int IMAGE_HEIGHT = 360;
constexpr const char *INPUT_FILE_PATH = "./assets/cube.obj";
constexpr IO::FileFormat INPUT_FILE_FORMAT = IO::FileFormat::OBJ;

constexpr int FPS = 30;
constexpr float DURATION = 2;
constexpr float NUM_CAMERA_ROTATIONS = 2;
constexpr const char *OUTPUT_FOLDER = "./videos/model/";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);
void update(Scene &scene, float t);
void update(Camera &camera, float t);
EntityId loadModel(EntityManager &em, const std::string &path);

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(5);

  init(scene);

  int frame = 1;
  float frameCount = DURATION * FPS;
  float step = 1. / frameCount;

  for (float t = 0; t < 1; t += step) {
    std::cout << std::endl;
    std::cout << "Frame: " << frame << std::endl;

    update(scene, t);
    renderer.render(scene);

    IO::save(renderer, OUTPUT_FOLDER + std::to_string(frame) + ".png", OUTPUT_FILE_FORMAT);
    frame++;
  }
}

void init(Scene &scene) {
  auto &camera = scene.getCamera();
  auto &em = scene.getEntityManager();

  init(camera);
  loadModel(em, INPUT_FILE_PATH);
}

void init(Camera &camera) {
  camera.setPitch(-30);
  camera.setPosition(Vec3(0, 1, 1));
}

void update(Scene &scene, float t) {
  auto &camera = scene.getCamera();
  update(camera, t);
}

void update(Camera &camera, float t) {
  float theta = 2 * PI * NUM_CAMERA_ROTATIONS * t;
  float yaw = -toDegrees(theta);

  Vec3 pos(std::sin(theta), 1, std::cos(theta));
  pos.x *= 2;
  pos.z *= 2;

  camera.setYaw(yaw);
  camera.setPosition(pos);
}

EntityId loadModel(EntityManager &em, const std::string &path) {
  auto model = em.createEntity();

  auto material = std::make_shared<Lambertian>(COLOR_GREY);
  auto mesh = std::make_shared<Mesh>();
  auto transform = std::make_shared<Transform>(Vec3(-0.5, -0.5, -0.5));

  IO::load(*mesh, path, INPUT_FILE_FORMAT);
  em.setAll(model, {mesh, material, transform});

  return model;
}
