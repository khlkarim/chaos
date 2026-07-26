#pragma once

#include "geometry/Ray.h"

class Skybox {
public:
  virtual Color getColor(const Ray &ray) const = 0;
};
