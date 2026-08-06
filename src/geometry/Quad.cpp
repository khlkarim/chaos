#include "geometry/Quad.h"

Quad::Quad(float l) : Mesh(computeVertices(l, l), computeIndices(l, l)) {}
Quad::Quad(float w, float h) : Mesh(computeVertices(w, h), computeIndices(w, h)) {}

std::vector<Vertex> Quad::computeVertices(float w, float h) {
  Vec3 dim(w, h, 0);

  std::vector<Vertex> vertices;
  std::vector<Vec3> directions = {
      {-0.5, -0.5, 0}, //
      {0.5, -0.5, 0},
      {-0.5, 0.5, 0},
      {0.5, 0.5, 0},
  };

  for (auto d : directions) {
    Vertex v;
    v.position = d * dim;
    v.texCoords = {d.x + 0.5f, 0.5f - d.y};
    vertices.push_back(v);
  }

  return vertices;
}

std::vector<unsigned int> Quad::computeIndices(float w, float h) { return {0, 1, 2, 1, 3, 2}; }
