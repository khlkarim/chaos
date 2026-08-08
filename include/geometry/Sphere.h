#pragma once

#include "components/Geometry.h"

class Sphere : public Geometry {
public:
  virtual Intersection intersect(const Ray &ray, const Transform &transform) const override;

private:
  static Vec2 getTexCoords(Vec3 n);
};
