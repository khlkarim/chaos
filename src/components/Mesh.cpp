#include "utils/math.h"
#include "components/Mesh.h"

Component::Type Mesh::getType() const { return TYPE; }

std::vector<Vertex> &Mesh::getVertices() { return vertices; }
const std::vector<Vertex> &Mesh::getVertices() const { return vertices; }
void Mesh::setVertices(const std::vector<Vertex> &v) { vertices = v; }

std::vector<unsigned int> &Mesh::getIndices() { return indices; }
const std::vector<unsigned int> &Mesh::getIndices() const { return indices; }
void Mesh::setIndices(const std::vector<unsigned int> &i) { indices = i; }

Intersection Mesh::intersect(const Ray &ray, const Transform &transform) const {
  Intersection inter, currInter;

  for (int i = 0; i < indices.size(); i += 3) {
    std::vector<Vertex> tri(3);
    std::vector<Vec3> edges(3);

    for (int j = 0; j < 3; j++) {
      tri[j] = vertices[indices[i + j]];
      tri[j].position = transform.apply(tri[j].position);
    }
    for (int j = 0; j < 3; j++) {
      edges[j] = tri[(j + 1) % 3].position - tri[j].position;
    }

    currInter.normal = normalize(cross(edges[0], -edges[2]));
    float distance = -dot(tri[0].position, currInter.normal);
    Vec3 rayDir = ray.getDirection(), rayOrig = ray.getOrigin();

    if (std::abs(dot(rayDir, currInter.normal)) < EPSILON) {
      continue;
    }

    currInter.t = -(dot(currInter.normal, rayOrig) + distance) / dot(currInter.normal, rayDir);
    if (currInter.t < 0) {
      continue;
    }

    bool inside = true;
    Vec3 n, p = ray.at(currInter.t);
    for (int j = 0; j < 3 && inside; j++) {
      n = normalize(cross(edges[j], p - tri[j].position));
      if (dot(n, currInter.normal) < 0) {
        inside = false;
      }
    }

    if (!inside) {
      continue;
    }

    if (inter.t == -1 || (currInter.t > 0 && currInter.t < inter.t)) {
      inter = currInter;
    }
  }

  if (inter.t > 0 && dot(inter.normal, ray.getDirection()) > 0) {
    inter.normal *= -1;
    inter.isFrontFace = false;
  }

  return inter;
}
