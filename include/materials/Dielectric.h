#pragma once

#include "components/Material.h"

class Dielectric : public Material {
public:
  Dielectric(float ri) : refractiveIndex(ri) {}

  float getRefractiveIndex() const;
  void setRefractiveIndex(float n);

  bool scatter(const Ray &ray, const Intersection &inter, Ray &scattered) const override;
  Color emit(Scene &scene, const Ray &ray, const Intersection &inter, const Color &scattered) const override;

private:
  float getReflectance(float a) const;

  float refractiveIndex;
};
