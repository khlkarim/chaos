#include <cmath>

#include "geometry/Sphere.h"

float Sphere::getRadius() const { return radius; }
void Sphere::setRadius(float r) { radius = r; }

Vec3 Sphere::getCenter() const { return center; }
void Sphere::setCenter(Vec3 c) { center = c; }

Intersection Sphere::intersect(const Ray &ray) const {
  Vec3 oc = center - ray.getOrigin();

  auto a = dot(ray.getDirection(), ray.getDirection());
  auto b = -2.0 * dot(ray.getDirection(), oc);
  auto c = dot(oc, oc) - radius * radius;

  auto discriminant = b * b - 4 * a * c;

  Vec3 normal;
  float t = -1;
  if (discriminant >= 0) {
    t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    normal = normalize(-1 * oc);
  }

  return {.t = t, .normal = normal};
}
