#pragma one

#include "components/Geometry.h"

class Sphere : public Geometry {
public:
  Sphere(float r = 1) : radius(r) {}

  float getRadius() const;
  void setRadius(float r);

  Intersection intersect(const Ray &ray, const Transform &transform) const override;

private:
  static Vec2 getTexCoords(Vec3 n);

  float radius;
};
