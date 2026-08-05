#pragma once

#include "components/Material.h"

class Dielectric : public Material {
public:
  Dielectric(float ri) : refractiveIndex(ri) {}

  float getRefractiveIndex() const;
  void setRefractiveIndex(float n);

  void scatter(Intersection &inter) const override;
  void emit(Scene &scene, Intersection &inter) const override;

private:
  float refractiveIndex;
};
