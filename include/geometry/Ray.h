#pragma once

#include "geometry/Vector.h"

class Ray {
public:
  Ray() = default;
  Ray(Vec3 o, Vec3 d) : origin(o), direction(d) {}

  Vec3 getOrigin() const;
  void setOrigin(Vec3 o);

  Vec3 getDirection() const;
  void setDirection(Vec3 d);

  Vec3 at(float t) const;

private:
  Vec3 origin;
  Vec3 direction;
};
