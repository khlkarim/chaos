#define SHARED_IMPLEMENTATION
#include "shared.h"

#include <cmath>
#include <string>
#include <iostream>
#include "utils/math.h"
#include "materials/Dielectric.h"

constexpr const char *MODEL_FILE_PATH = "./assets/models/cube.obj";
constexpr IO::FileFormat MODEL_FILE_FORMAT = IO::FileFormat::OBJ;

constexpr int FPS = 30;
constexpr float DURATION = 2;
constexpr float NUM_CAMERA_ROTATIONS = 2;
constexpr const char *OUTPUT_FOLDER = "./videos/model/";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);
void update(Scene &scene, float t);
void update(Camera &camera, float t);

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(RENDERER_SAMPLES_PER_PIXEL);
  renderer.setMaxDepth(RENDERER_MAX_DEPTH);

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

  auto cube = loadModel(scene, MODEL_FILE_PATH, MODEL_FILE_FORMAT);

  auto material = std::make_shared<Dielectric>(1.5);
  auto transform = std::make_shared<Transform>(Vec3(-0.5, -0.5, -0.5));
  em.setAll(cube, {material, transform});
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
