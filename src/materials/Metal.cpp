#include "materials/Metal.h"

float Metal::getFuzz() const { return fuzz; }
void Metal::setFuzz(float f) { fuzz = f; }

Color Metal::getAlbedo() const { return albedo; }
void Metal::setAlbedo(Color c) { albedo = c; }

Color Metal::mix(const Color &color) const { return color * albedo; }

Ray Metal::reflect(const Ray &ray, const Intersection &inter) const {
  Vec3 rand = Vec3::getRandomUnitSphere();
  Vec3 dir = ray.getDirection().reflect(inter.normal);

  Vec3 origin = inter.p;
  Vec3 direction = dir + fuzz * rand;

  return Ray(origin, direction);
}
