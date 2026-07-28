#pragma once

#include "entity/Entity.h"
#include "geometry/Vector.h"

struct Intersection {
  Vec3 normal;
  float t = -1;
  bool isFrontFace = true;
  EntityId eId = EntityManager::NIL;
};
