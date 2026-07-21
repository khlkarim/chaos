#pragma once

#include "geometry/Ray.h"

struct Intersection {
  float t;
  Vec3 normal;
};

class Entity {
public:
  virtual Intersection intersect(const Ray &ray) const = 0;
};
