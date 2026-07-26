#pragma once

#include "components/Material.h"

class Metal : public Material {
public:
  Metal(Color albedo = Color(1), float fuzz = 0) : albedo(albedo), fuzz(fuzz) {}

  float getFuzz() const;
  void setFuzz(float f);

  Color getAlbedo() const;
  void setAlbedo(Color c);

  Color mix(const Color &color) const override;
  Ray reflect(const Ray &ray, const Intersection &inter) const override;

private:
  float fuzz;
  Color albedo;
};
