#pragma once

#include "geometry/Mesh.h"

class OBJ {
public:
  static std::shared_ptr<Mesh> loadMesh(const std::string &path);
};
