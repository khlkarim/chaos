#include <cmath>

#include "utils/math.h"
#include "geometry/Sphere.h"

Intersection Sphere::intersect(const Ray &ray, const Transform &transform) const {
  Intersection inter;
  Vec3 origin = ray.getOrigin();
  Vec3 rayDir = ray.getDirection();
  Vec3 center = transform.getPosition();
  float radius = transform.getScale().x;

  Vec3 oc = center - origin;
  auto a = rayDir.length2();
  auto b = -2.0 * dot(rayDir, oc);
  auto c = oc.length2() - radius * radius;

  auto discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    float t = -1;
    if (c > 0) {
      t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    } else {
      t = (-b + std::sqrt(discriminant)) / (2.0 * a);
    }

    Vec3 pos = ray.at(t);
    Vec3 normal = normalize(pos - center);

    inter.setT(t);
    inter.setIncidentRay(ray);
    inter.setNormal(normal, rayDir);
    inter.setTexCoords(getTexCoords(inter.getNormal()));
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
