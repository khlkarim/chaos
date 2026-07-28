#include "utils/math.h"
#include "materials/Metal.h"

float Metal::getFuzz() const { return fuzz; }
void Metal::setFuzz(float f) { fuzz = f; }

Color Metal::getAlbedo() const { return albedo; }
void Metal::setAlbedo(Color c) { albedo = c; }

Color Metal::mix(const Color &color) const { return color * albedo; }

Ray Metal::reflect(const Ray &ray, const Intersection &inter) const {
  Ray reflected;
  Vec3 dir = ray.getDirection();
  Vec3 rand = Vec3::getRandomUnitSphere();
  reflected.setOrigin(ray.at(inter.t - EPSILON));
  reflected.setDirection(normalize(dir.reflect(inter.normal) + fuzz * rand));
  return reflected;
}
