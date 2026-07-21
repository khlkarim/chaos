#pragma once

#include <vector>

#include "renderer/Entity.h"

struct Vertex {
  Color color;
  Vec3 normal;
  Vec3 position;
  Vec2 textureCoords;
};

struct Transform {
  Vec3 position;
  Vec3 scale = Vec3(1);
};

class Mesh : public Entity {
public:
  Transform transform;
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  Intersection intersect(const Ray &ray) const override;
};
