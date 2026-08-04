#pragma once

#include "geometry/Mesh.h"

class Quad : public Mesh {
public:
  Quad(float l = 1);
  Quad(float w, float h);

  static std::vector<Vertex> computeVertices(float w, float h);
  static std::vector<unsigned int> computeIndices(float w, float h);
};
