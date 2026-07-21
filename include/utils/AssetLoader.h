#pragma once

#include <string>

#include "geometry/Mesh.h"

class AssetLoader {
public:
  static Mesh load(const std::string &path);
};
