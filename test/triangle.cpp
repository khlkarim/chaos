#include <memory>

#include "io/IO.h"
#include "components/Mesh.h"
#include "geometry/Vector.h"
#include "renderer/Renderer.h"
#include "materials/Lambertian.h"

constexpr int IMAGE_WIDTH = 640;
constexpr int IMAGE_HEIGHT = 360;
constexpr const char *OUTPUT_FILE_PATH = "triangle-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

void init(Scene &scene);
void init(Camera &camera);
EntityId createTriangle(EntityManager &em);

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
  createTriangle(em);
}

void init(Camera &camera) {
  camera.setYaw(30);
  camera.setPitch(-30);
  camera.setPosition(Vec3(-1, 1, 1));
}

EntityId createTriangle(EntityManager &em) {
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

  auto mat = std::make_shared<Lambertian>(COLOR_GREY);
  auto transform = std::make_shared<Transform>(Vec3(0, 0, -1));
  auto mesh = std::make_shared<Mesh>(vertices, indices);
  em.setAll(triangle, {mat, mesh, transform});

  return triangle;
}
