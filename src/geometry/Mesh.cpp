#include "utils/math.h"
#include "geometry/Mesh.h"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
    : vertices(vertices), indices(indices) {
  computeNormals(this->vertices, this->indices);
}

std::vector<Vertex> &Mesh::getVertices() { return vertices; }
const std::vector<Vertex> &Mesh::getVertices() const { return vertices; }
void Mesh::setVertices(const std::vector<Vertex> &v) { vertices = v; }

std::vector<unsigned int> &Mesh::getIndices() { return indices; }
const std::vector<unsigned int> &Mesh::getIndices() const { return indices; }
void Mesh::setIndices(const std::vector<unsigned int> &i) { indices = i; }

Intersection Mesh::intersect(const Ray &ray, const Transform &transform) const {
  Intersection inter;

  for (int i = 0; i < indices.size(); i += 3) {
    std::vector<Vertex> tri(3);
    std::vector<Vec3> edges(3);

    for (int j = 0; j < 3; j++) {
      tri[j] = vertices[indices[i + j]];
      tri[j].position = transform.apply(tri[j].position);
      tri[j].normal = normalize(tri[j].normal.rotate(transform.getRotation()));
    }
    for (int j = 0; j < 3; j++) {
      edges[j] = tri[(j + 1) % 3].position - tri[j].position;
    }

    Vec3 normal = normalize(cross(edges[0], -edges[2]));
    float distance = -dot(tri[0].position, normal);
    Vec3 rayDir = ray.getDirection(), rayOrig = ray.getOrigin();

    if (std::abs(dot(rayDir, normal)) < EPSILON) {
      continue;
    }

    float t = -(dot(normal, rayOrig) + distance) / dot(normal, rayDir);
    if (t < 0) {
      continue;
    }

    bool inside = true;
    Vec3 n, p = ray.at(t);
    for (int j = 0; j < 3 && inside; j++) {
      n = normalize(cross(edges[j], p - tri[j].position));
      if (dot(n, normal) < 0) {
        inside = false;
      }
    }

    if (!inside) {
      continue;
    }

    if (inter.getT() == -1 || (t > 0 && t < inter.getT())) {
      Vec3 uvw = getBarycentricCoords(tri, p);
      Vec3 n0 = tri[0].normal, n1 = tri[1].normal, n2 = tri[2].normal;
      Vec2 tex0 = tri[0].texCoords, tex1 = tri[1].texCoords, tex2 = tri[2].texCoords;

      inter.setT(t);
      inter.setIncidentRay(ray);
      inter.setTexCoords(uvw.x * tex1 + uvw.y * tex2 + uvw.z * tex0);
      inter.setNormal(uvw.x * n1 + uvw.y * n2 + uvw.z * n0, rayDir);
    }
  }

  return inter;
}

void Mesh::computeNormals(std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
  for (int j = 0; j < indices.size(); j += 3) {
    Vec3 a = vertices[indices[j + 1]].position - vertices[indices[j]].position;
    Vec3 b = vertices[indices[j + 2]].position - vertices[indices[j]].position;

    Vec3 n = cross(a, b);
    vertices[indices[j]].normal += n;
    vertices[indices[j + 1]].normal += n;
    vertices[indices[j + 2]].normal += n;
  }

  for (int j = 0; j < vertices.size(); j++) {
    vertices[j].normal = normalize(vertices[j].normal);
  }
}

Vec3 Mesh::getBarycentricCoords(const std::vector<Vertex> &tri, Vec3 p) {
  std::vector<Vec3> edges(3);
  for (int j = 0; j < 3; j++) {
    edges[j] = tri[(j + 1) % 3].position - tri[j].position;
  }

  Vec3 toP = p - tri[0].position;
  Vec3 A = cross(edges[0], -edges[2]);

  float AT = A.length() / 2;
  float AN = cross(toP, edges[0]).length() / 2;
  float AM = cross(toP, -edges[2]).length() / 2;

  float u = AM / AT;
  float v = AN / AT;
  float w = 1 - u - v;

  return Vec3(u, v, w);
}
