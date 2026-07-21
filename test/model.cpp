#include <memory>

#include "renderer/Renderer.h"
#include "utils/AssetLoader.h"

constexpr int IMAGE_WIDTH = 1280;
constexpr int IMAGE_HEIGHT = 720;
constexpr FileFormat OUTPUT_FILE_FORMAT = PNG;
constexpr const char *OUTPUT_FILE_PATH = "cube-output-01.png";
constexpr const char *MODEL_FILE_PATH = "./assets/cube.obj";

int main() {
  Scene scene;
  Camera &camera = scene.getCamera();
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);

  camera.setPosition(Vec3(1));
  camera.setPitch(-30);
  camera.setYaw(-30);

  auto cube = std::make_shared<Mesh>(AssetLoader::load(MODEL_FILE_PATH));
  cube->transform.position = Vec3(-0.5, -0.5, -1);

  scene.entities.push_back(cube);

  renderer.render(scene);
  renderer.write(OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}
