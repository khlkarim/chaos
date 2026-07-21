#pragma one

#include "renderer/Entity.h"

class Sphere : public Entity {
public:
  Sphere(float r, Vec3 c) : radius(r), center(c) {}

  float getRadius() const;
  void setRadius(float r);

  Vec3 getCenter() const;
  void setCenter(Vec3 c);

  Intersection intersect(const Ray &ray) const override;

private:
  float radius;
  Vec3 center;
};
