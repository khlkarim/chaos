#include <cmath>

#include "utils/math.h"
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
    inter.texCoords = getTexCoords(inter.normal);

    if (dot(inter.normal, dir) > 0) {
      inter.normal *= -1;
      inter.isFrontFace = false;
    }
  }

  return inter;
}

Vec2 Sphere::getTexCoords(Vec3 n) {
  float phi = std::acos(n.y);
  float theta = std::atan2(-n.z, n.x) + PI;

  float u = theta / (2 * PI);
  float v = phi / PI;

  return Vec2(u, v);
}
