#pragma once

#include "entity/Entity.h"
#include "geometry/Vector.h"

struct Intersection {
  float t = -1;
  Vec3 normal;
  Vec2 texCoords;
  bool isFrontFace = true;
  EntityId eId = EntityManager::NIL;
};
