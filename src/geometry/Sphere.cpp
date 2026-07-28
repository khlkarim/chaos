#include <cmath>

#include "geometry/Sphere.h"

float Sphere::getRadius() const { return radius; }
void Sphere::setRadius(float r) { radius = r; }

Intersection Sphere::intersect(const Ray &ray, const Transform &transform) const {
  Intersection inter;

  Vec3 dir = ray.getDirection();
  Vec3 origin = ray.getOrigin();
  Vec3 center = transform.getPosition();

  Vec3 oc = center - origin;
  auto a = dir.length2();
  auto b = -2.0 * dot(dir, oc);
  auto c = oc.length2() - radius * radius;

  auto discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    if (c > 0) {
      inter.t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    } else {
      inter.t = (-b + std::sqrt(discriminant)) / (2.0 * a);
    }
    Vec3 pos = ray.at(inter.t);
    inter.normal = normalize(pos - center);

    if (dot(inter.normal, dir) > 0) {
      inter.normal *= -1;
      inter.isFrontFace = false;
    }
  }

  return inter;
}
