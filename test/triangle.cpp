#include <memory>

#include "geometry/Mesh.h"
#include "renderer/Camera.h"
#include "renderer/Renderer.h"

constexpr int IMAGE_WIDTH = 1280;
constexpr int IMAGE_HEIGHT = 720;
constexpr FileFormat OUTPUT_FILE_FORMAT = PNG;
constexpr const char *OUTPUT_FILE_PATH = "triangle-output-01.png";

int main() {
  Scene scene;
  Camera &camera = scene.getCamera();
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);

  camera.setPosition(Vec3(-1, 1, 1));
  camera.setPitch(-30);
  camera.setYaw(30);

  std::vector<u32> indices = {0, 1, 2};
  std::vector<Vertex> vertices = {
      {
          .normal = Vec3(0, 0, 1),
          .position = Vec3(-1, -1, 0),
      },
      {

          .normal = Vec3(0, 0, 1),
          .position = Vec3(1, -1, 0),
      },
      {
          .normal = Vec3(0, 0, 1),
          .position = Vec3(0, 1, 0),
      },
  };

  auto e = std::make_shared<Mesh>();
  e->indices = indices;
  e->vertices = vertices;
  e->transform.position.z = -1;

  scene.entities.push_back(e);

  renderer.render(scene);
  renderer.write(OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}
