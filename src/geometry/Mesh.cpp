#include "geometry/Mesh.h"
#include "utils/math.h"

Intersection Mesh::intersect(const Ray &ray) const {
  int closestIdx = -1;
  float closestT = -1;

  for (int i = 0; i < indices.size(); i += 3) {
    std::vector<Vertex> tri(3);
    for (int j = 0; j < 3; j++) {
      tri[j] = vertices[indices[i + j]];
      tri[j].position = tri[j].position * transform.scale + transform.position;
    }

    Vec3 normal = tri[0].normal;
    float distance = -dot(tri[0].position, normal);
    Vec3 rayDir = ray.getDirection(), rayOrig = ray.getOrigin();

    if (std::abs(dot(rayDir, normal)) < EPSILON) {
      continue;
    }

    float t = -(dot(normal, rayOrig) + distance) / dot(normal, rayDir);
    if (t < 0) {
      continue;
    }

    Vec3 n, p = rayOrig + t * rayDir;
    Vec3 v0v1 = tri[1].position - tri[0].position;
    Vec3 v0v2 = tri[2].position - tri[0].position;

    if (dot(cross(v0v1, v0v2), normal) < 0) {
      Vertex tmp = tri[1];
      tri[1] = tri[2];
      tri[2] = tmp;

      Vec3 t = v0v1;
      v0v1 = v0v2;
      v0v2 = t;
    }

    Vec3 v0p = p - tri[0].position;
    n = cross(v0v1, v0p);
    if (dot(normal, n) < 0)
      continue;

    Vec3 v2v1 = tri[2].position - tri[1].position;
    Vec3 v1p = p - tri[1].position;
    n = cross(v2v1, v1p);
    if (dot(normal, n) < 0)
      continue;

    Vec3 v2v0 = tri[0].position - tri[2].position;
    Vec3 v2p = p - tri[2].position;
    n = cross(v2v0, v2p);
    if (dot(normal, n) < 0)
      continue;

    if (closestIdx == -1 || t < closestT) {
      closestT = t;
      closestIdx = i;
    }
  }

  Vec3 normal;
  if (closestIdx != -1) {
    normal = vertices[indices[closestIdx]].normal;
  }

  return {.t = closestT, .normal = normal};
}
