#pragma once

#include "entity/Entity.h"
#include "geometry/Vector.h"

struct Intersection {
  Vec3 p;
  Vec3 normal;
  float t = -1;
  EntityId eId = EntityManager::NIL;
};
