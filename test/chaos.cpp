#include <map>
#include <memory>
#include <vector>

#include "utils/math.h"

#include "io/IO.h"
#include "geometry/Sphere.h"
#include "materials/Metal.h"
#include "materials/Dielectric.h"
#include "materials/Lambertian.h"

constexpr int IMAGE_WIDTH = 640;
constexpr int IMAGE_HEIGHT = 360;
constexpr const char *OUTPUT_FILE_PATH = "chaos-output-02.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;
constexpr const char *CUBE_FILE_PATH = "./assets/cube.obj";
constexpr IO::FileFormat CUBE_FILE_FORMAT = IO::FileFormat::OBJ;
constexpr const char *TRIANGLE_FILE_PATH = "./assets/triangle.crtscene";
constexpr IO::FileFormat TRIANGLE_FILE_FORMAT = IO::FileFormat::CRT;

constexpr float CELL_SIZE = 0.3;
constexpr float CHARACTER_GAP = 0.4;
constexpr int FONT_WIDTH = 6, FONT_HEIGHT = 9;
using Font = std::map<char, std::vector<int>>;
Font font;

void init(Font &font);
void init(Scene &scene);
void init(Camera &camera);
void drawCharacter(Scene &scene, char c, Vec3 center);
void drawWord(Scene &scene, const std::string &s, Vec3 center);
EntityId drawCube(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat);
EntityId drawTriangle(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat);
EntityId drawSphere(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat);
std::shared_ptr<Material> getRandomMaterial();

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);

  init(font);
  init(scene);
  renderer.render(scene);
  IO::save(renderer, OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}

void init(Scene &scene) {
  auto &camera = scene.getCamera();
  auto &em = scene.getEntityManager();

  init(camera);
  drawWord(scene, "CHAOS", Vec3(0, 0, -1));
}

void init(Camera &camera) { camera.setPosition(Vec3(0, 0, 2.5)); }

void drawWord(Scene &scene, const std::string &s, Vec3 center) {
  float gap = CHARACTER_GAP;
  float characterWidth = FONT_WIDTH * CELL_SIZE;
  float x = 0.5 * (s.length() * (characterWidth + gap) - gap);

  Vec3 start = center - Vec3(x, 0, 0);
  start += Vec3(0.5 * characterWidth, 0, 0);

  for (auto c : s) {
    drawCharacter(scene, c, start);
    start += Vec3(characterWidth + gap, 0, 0);
  }
}

void drawCharacter(Scene &scene, char c, Vec3 center) {
  std::vector<int> grid = font[c];
  auto &em = scene.getEntityManager();

  Vec3 uv = Vec3(FONT_WIDTH, FONT_HEIGHT, 0);
  Vec3 dUV = Vec3(CELL_SIZE, -CELL_SIZE, 0);
  Vec3 cell00 = center - 0.5 * dUV * (uv + Vec3(1));

  for (int i = 0; i < FONT_WIDTH; i++) {
    for (int j = 0; j < FONT_HEIGHT; j++) {
      int idx = j * FONT_WIDTH + i;
      Vec3 center = cell00 + Vec3(i, j, 0) * dUV;

      if (grid[idx] == 1) {
        int rand = 2;
        // int rand = getRandomInt(0, 3);

        auto mat = getRandomMaterial();
        auto transform = std::make_shared<Transform>(center, Vec3(CELL_SIZE));

        if (rand == 0) {
          drawCube(em, transform, mat);
        } else if (rand == 1) {
          drawTriangle(em, transform, mat);
        } else if (rand == 2) {
          drawSphere(em, transform, mat);
        }
      }
    }
  }
}

EntityId drawCube(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat) {
  auto cube = em.createEntity();

  auto mesh = std::make_shared<Mesh>();
  IO::load(*mesh, CUBE_FILE_PATH, CUBE_FILE_FORMAT);
  em.setAll(cube, {mesh, transform, mat});

  return cube;
}

EntityId drawTriangle(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat) {
  auto triangle = em.createEntity();

  auto mesh = std::make_shared<Mesh>();
  IO::load(*mesh, TRIANGLE_FILE_PATH, TRIANGLE_FILE_FORMAT);
  em.setAll(triangle, {mesh, transform, mat});

  return triangle;
}

EntityId drawSphere(EntityManager &em, std::shared_ptr<Transform> transform, std::shared_ptr<Material> mat) {
  auto s = em.createEntity();

  float radius = transform->getScale().x;
  auto sdf = std::make_shared<Sphere>(radius);
  em.setAll(s, {mat, sdf, transform});

  return s;
}

std::shared_ptr<Material> getRandomMaterial() {
  auto f = getRandomFLoat();
  auto color = Color::getRandom();
  color.w = 1;

  std::vector<std::shared_ptr<Material>> materials = {
      std::make_shared<Dielectric>(1 + f),
      std::make_shared<Lambertian>(color),
      std::make_shared<Metal>(color, f),
  };

  return materials[getRandomInt(0, 3)];
}

void init(Font &font) {
  font['C'] = {
      0, 1, 1, 1, 1, 0, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 0, //
      1, 0, 0, 0, 0, 0, //
      1, 0, 0, 0, 0, 0, //
      1, 0, 0, 0, 0, 0, //
      1, 0, 0, 0, 0, 0, //
      1, 0, 0, 0, 0, 1, //
      0, 1, 1, 1, 1, 0, //
  };

  font['H'] = {
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 1, 1, 1, 1, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
  };

  font['A'] = {
      0, 0, 1, 1, 0, 0, //
      0, 1, 0, 0, 1, 0, //
      0, 1, 0, 0, 1, 0, //
      0, 1, 0, 0, 1, 0, //
      1, 1, 1, 1, 1, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
  };

  font['O'] = {
      0, 1, 1, 1, 1, 0, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      0, 1, 1, 1, 1, 0, //
  };

  font['S'] = {
      0, 1, 1, 1, 1, 0, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      0, 1, 0, 0, 0, 0, //
      0, 0, 1, 1, 0, 0, //
      0, 0, 0, 0, 1, 0, //
      1, 0, 0, 0, 0, 1, //
      1, 0, 0, 0, 0, 1, //
      0, 1, 1, 1, 1, 0, //
  };
}
