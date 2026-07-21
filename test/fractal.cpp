#include <cmath>
#include <memory>

#include "geometry/Circle.h"
#include "geometry/Rectangle.h"
#include "renderer/Renderer.h"
#include "utils/math.h"

constexpr int IMAGE_WIDTH = 720;
constexpr int IMAGE_HEIGHT = 720;
constexpr FileFormat OUTPUT_FILE_FORMAT = PNG;
constexpr const char *OUTPUT_FILE_PATH = "fractal-output-01.png";

constexpr int FRACTAL_DEPTH = 7;
constexpr int FRACTAL_DEGREE = 9;
constexpr int FRACTAL_SPREAD = 2;
constexpr bool FRACTAL_USE_RECTANGLES = true;

std::vector<Vec2> getDirections(const int degree);
void drawFractalRectangle(Rectangle &r, const int depth, const int degree, const float spread);
void drawFractalCircle(Circle &c, const int depth, const int degree, const float spread);

int main() {
  auto renderer = std::make_shared<Renderer>(IMAGE_WIDTH, IMAGE_HEIGHT);

  if constexpr (FRACTAL_USE_RECTANGLES) {
    Rectangle shape;
    shape.width = 0.25;
    shape.height = 0.25;
    shape.center = {0, 0};
    shape.color = {0.1, 0.9, 0.8, 1};
    shape.setRenderer(renderer);

    drawFractalRectangle(shape, FRACTAL_DEPTH, FRACTAL_DEGREE, FRACTAL_SPREAD);
  } else {
    Circle shape;
    shape.radius = 0.125;
    shape.center = {0, 0};
    shape.color = {1, 1, 0, 1};
    shape.setRenderer(renderer);

    drawFractalCircle(shape, FRACTAL_DEPTH, FRACTAL_DEGREE, FRACTAL_SPREAD);
  }

  renderer->write(OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}

void drawFractalRectangle(Rectangle &r, const int depth, const int degree, const float spread) {
  if (depth == 0) {
    return;
  }

  r.color.x += 0.1;
  r.color.y -= 0.1;
  r.color.z *= 0.8;

  r.draw();

  Vec2 wh = {r.width, r.height};
  std::vector<Vec2> directions = getDirections(degree);

  r.width /= 2;
  r.height /= 2;
  for (int i = 0; i < directions.size(); i++) {
    r.center += directions[i] * wh * spread;
    drawFractalRectangle(r, depth - 1, degree, spread);
    r.center -= directions[i] * wh * spread;
  }
  r.width = wh.x;
  r.height = wh.y;
}

void drawFractalCircle(Circle &c, const int depth, const int degree, const float spread) {
  if (depth == 0) {
    return;
  }

  c.color.x += 0.1;
  c.color.y -= 0.1;
  c.color.z *= 0.8;

  c.draw();

  float r = c.radius;
  std::vector<Vec2> directions = getDirections(degree);

  c.radius /= 2;
  for (int i = 0; i < directions.size(); i++) {
    c.center += directions[i] * r * spread;
    drawFractalCircle(c, depth - 1, degree, spread);
    c.center -= directions[i] * r * spread;
  }
  c.radius = r;
}

std::vector<Vec2> getDirections(const int degree) {
  std::vector<Vec2> directions;

  float theta = 0;
  float thetaStep = 2 * PI / degree;
  for (int i = 0; i < degree; i++) {
    directions.push_back({std::cos(theta), std::sin(theta)});
    theta += thetaStep;
  }

  return directions;
}
