#define SHARED_IMPLEMENTATION
#include "shared.h"

#include "utils/math.h"
#include "materials/Metal.h"
#include "materials/Dielectric.h"
#include "materials/Lambertian.h"

constexpr const char *OUTPUT_FILE_PATH = "chaos-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

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
std::shared_ptr<Material> getRandomMaterial();

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(RENDERER_SAMPLES_PER_PIXEL);
  renderer.setMaxDepth(RENDERER_MAX_DEPTH);

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
  float x = 0.5 * s.length() * (characterWidth + gap);

  Vec3 start = center - Vec3(x, 0, 0);
  start += Vec3(0.5 * (characterWidth + gap), 0, 0);

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
  Vec3 cell00 = center - 0.5 * dUV * uv + 0.5 * dUV;

  for (int i = 0; i < FONT_WIDTH; i++) {
    for (int j = 0; j < FONT_HEIGHT; j++) {
      int idx = j * FONT_WIDTH + i;
      Vec3 center = cell00 + Vec3(i, j, 0) * dUV;

      if (grid[idx] == 1) {
        auto mat = getRandomMaterial();
        auto transform = std::make_shared<Transform>(center, Vec3(CELL_SIZE));
        drawSphere(scene, {transform, mat});
      }
    }
  }
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
