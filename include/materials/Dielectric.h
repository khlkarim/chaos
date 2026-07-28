#pragma once

#include "components/Material.h"

class Dielectric : public Material {
public:
  Dielectric(float ri) : refractiveIndex(ri) {}

  float getRefractiveIndex() const;
  void setRefractiveIndex(float n);

  Color mix(const Color &color) const override;
  Ray reflect(const Ray &ray, const Intersection &inter) const override;

private:
  float getReflectance(float a) const;

  float refractiveIndex;
};
