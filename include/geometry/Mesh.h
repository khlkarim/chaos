#pragma once

#include <vector>

#include "geometry/Vertex.h"
#include "components/Geometry.h"

class Mesh : public Geometry {
public:
  Mesh() = default;
  Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

  std::vector<Vertex> &getVertices();
  const std::vector<Vertex> &getVertices() const;
  void setVertices(const std::vector<Vertex> &v);

  std::vector<unsigned int> &getIndices();
  const std::vector<unsigned int> &getIndices() const;
  void setIndices(const std::vector<unsigned int> &i);

  Intersection intersect(const Ray &ray, const Transform &transform = Transform()) const override;

  static Vec3 getBarycentricCoords(const std::vector<Vertex> &tri, Vec3 p);
  static void computeNormals(std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

protected:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
};
