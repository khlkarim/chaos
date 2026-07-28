#include "utils/math.h"
#include "materials/Lambertian.h"

Color Lambertian::getAlbedo() const { return albedo; }
void Lambertian::setAlbedo(Color c) { albedo = c; }

Color Lambertian::mix(const Color &color) const { return color * albedo; }

Ray Lambertian::reflect(const Ray &ray, const Intersection &inter) const {
  Ray reflected;
  Vec3 rand = Vec3::getRandomUnitSphere();
  reflected.setOrigin(ray.at(inter.t - EPSILON));
  reflected.setDirection(normalize(inter.normal + rand));
  return reflected;
}
