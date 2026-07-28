#include <memory>

#include "io/IO.h"
#include "components/Mesh.h"
#include "renderer/Renderer.h"
#include "materials/Lambertian.h"

constexpr int IMAGE_WIDTH = 320;
constexpr int IMAGE_HEIGHT = 180;
constexpr const char *OUTPUT_FILE_PATH = "triangle-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);
EntityId drawTriangle(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat);

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

  auto mat = std::make_shared<Lambertian>(COLOR_GREY);
  auto transform = std::make_shared<Transform>(Vec3(0, 0, -1));
  drawTriangle(em, transform, mat);
}

void init(Camera &camera) {
  camera.setYaw(30);
  camera.setPitch(-30);
  camera.setPosition(Vec3(-1, 1, 1));
}

EntityId drawTriangle(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat) {
  auto triangle = em.createEntity();

  std::vector<unsigned int> indices = {0, 1, 2};
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

  auto mesh = std::make_shared<Mesh>(vertices, indices);
  em.setAll(triangle, {mat, mesh, transform});

  return triangle;
}
