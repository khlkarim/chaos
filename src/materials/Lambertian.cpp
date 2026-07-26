#include "materials/Lambertian.h"

Color Lambertian::getAlbedo() const { return albedo; }
void Lambertian::setAlbedo(Color c) { albedo = c; }

Color Lambertian::mix(const Color &color) const { return color * albedo; }

Ray Lambertian::reflect(const Ray &ray, const Intersection &inter) const {
  Vec3 rand = Vec3::getRandomUnitSphere();

  Vec3 origin = inter.p;
  Vec3 direction = inter.normal + rand;

  return Ray(origin, direction);
}
