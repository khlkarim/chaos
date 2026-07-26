#include "skybox/Sky.h"

Color Sky::getStartColor() const { return start; }
void Sky::setStartColor(Color c) { start = c; }

Color Sky::getEndColor() const { return end; }
void Sky::setEndColor(Color c) { end = c; }

Color Sky::getColor(const Ray &ray) const {
  Vec3 d = ray.getDirection();
  auto a = 0.5 * (d.y + 1.0);
  return (1 - a) * start + a * end;
}
