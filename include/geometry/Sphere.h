#pragma once

#include "components/Geometry.h"

class Sphere : public Geometry {
public:
  Intersection intersect(const Ray &ray, const Transform &transform) const override;

private:
  static Vec2 getTexCoords(Vec3 n);
};
