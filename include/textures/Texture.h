#pragma once

#include "geometry/Vector.h"

class Texture {
public:
  virtual ~Texture() {}
  virtual Color at(Vec2 texCoords) const = 0;
};
