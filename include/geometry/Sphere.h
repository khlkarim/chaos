#pragma one

#include "components/SDF.h"

class Sphere : public SDF {
public:
  Sphere(float r = 1) : radius(r) {}

  float getRadius() const;
  void setRadius(float r);

  Intersection intersect(const Ray &ray, const Transform &transform) const override;

private:
  float radius;
};
