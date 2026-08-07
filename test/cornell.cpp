#define SHARED_IMPLEMENTATION
#include "shared.h"

#include "skybox/Monochrome.h"
#include "materials/Emissive.h"
#include "materials/Dielectric.h"
#include "materials/Lambertian.h"

constexpr const char *OUTPUT_FILE_PATH = "cornell-output-01.png";
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

  auto skybox = std::make_shared<Monochrome>(COLOR_BLACK);
  scene.setSkybox(skybox);

  auto lightMat = std::make_shared<Emissive>(COLOR_WHITE);
  auto lightTransform = std::make_shared<Transform>(Vec3(0, 0.9, 0));
  createLight(scene, {lightTransform, lightMat});

  auto red = std::make_shared<Lambertian>(Color(.65, .05, .05, 1));
  auto white = std::make_shared<Lambertian>(Color(.73, .73, .73, 1));
  auto green = std::make_shared<Lambertian>(Color(.12, .45, .15, 1));

  auto backT = std::make_shared<Transform>(Vec3(0, 0, -1), 2);
  drawQuad(scene, {backT, white});

  auto topT = std::make_shared<Transform>(Vec3(0, 1, 0), 2);
  topT->setRotation(Vec3(toRadians(90), 0, 0));
  drawQuad(scene, {topT, white});

  auto bottomT = std::make_shared<Transform>(Vec3(0, -1, 0), 2);
  bottomT->setRotation(Vec3(toRadians(-90), 0, 0));
  drawQuad(scene, {bottomT, white});

  auto leftT = std::make_shared<Transform>(Vec3(-1, 0, 0), 2);
  leftT->setRotation(Vec3(0, toRadians(-90), 0));
  drawQuad(scene, {leftT, green});

  auto rightT = std::make_shared<Transform>(Vec3(1, 0, 0), 2);
  rightT->setRotation(Vec3(0, toRadians(90), 0));
  drawQuad(scene, {rightT, red});

  auto leftMat = std::make_shared<Dielectric>(1.5);
  auto leftTransform = std::make_shared<Transform>(Vec3(0, 0, 0), Vec3(0.5));
  drawSphere(scene, {leftTransform, leftMat});
}

void init(Camera &camera) { camera.setPosition(Vec3(0, 0, 2)); }
