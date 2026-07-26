#include <cmath>

#include "geometry/Sphere.h"

float Sphere::getRadius() const { return radius; }
void Sphere::setRadius(float r) { radius = r; }

Intersection Sphere::intersect(const Ray &ray, const Transform &transform) const {
  Vec3 oc = transform.getPosition() - ray.getOrigin();

  auto a = dot(ray.getDirection(), ray.getDirection());
  auto b = -2.0 * dot(ray.getDirection(), oc);
  auto c = dot(oc, oc) - radius * radius;

  auto discriminant = b * b - 4 * a * c;

  Intersection inter;
  if (discriminant >= 0) {
    inter.t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    inter.normal = normalize(-1 * oc);
  }

  return inter;
}
