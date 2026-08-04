#pragma once

#include "geometry/Mesh.h"

class OBJ {
public:
  static void load(Mesh &mesh, const std::string &path);
};
