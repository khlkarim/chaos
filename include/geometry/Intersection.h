#pragma once

#include "utils/math.h"
#include "geometry/Ray.h"
#include "entity/Entity.h"

class Intersection {
public:
  float getReflectionBias() const;
  void setReflectionBias(float f);

  float getRefractionBias() const;
  void setRefractionBias(float f);

  Vec3 getIntersectionOrigin() const;
  Vec3 getReflectionOrigin() const;
  Vec3 getRefractionOrigin() const;

  Ray &getIncidentRay();
  const Ray &getIncidentRay() const;
  void setIncidentRay(Ray r);

  std::vector<Ray> &getScatteredRays();
  const std::vector<Ray> &getScatteredRays() const;
  void setScatteredRays(const std::vector<Ray> &r);

  float getT() const;
  void setT(float t);

  Vec3 getNormal() const;
  Vec3 getTriNormal() const;
  void setNormal(Vec3 outwardNormal, Vec3 rayDir);
  void setTriNormal(Vec3 outwardNormal, Vec3 rayDir);
  bool getIsFrontFace() const;

  Vec2 getTexCoords() const;
  void setTexCoords(Vec2 t);

  EntityId getEntity() const;
  void setEntity(EntityId e);

  friend bool operator<(const Intersection &lhs, const Intersection &rhs);

private:
  float reflectionBias = EPSILON;
  float refractionBias = EPSILON;

  Ray incident;
  float t = -1;
  std::vector<Ray> scattered;

  Vec3 normal;
  Vec3 triNormal;
  Vec2 texCoords;
  bool isFrontFace = true;
  EntityId eId = EntityManager::NIL;
};
