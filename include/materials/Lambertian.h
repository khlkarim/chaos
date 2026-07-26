#pragma once

#include "components/Material.h"

class Lambertian : public Material {
public:
  Lambertian(Color albedo = Color(1)) : albedo(albedo) {}

  Color getAlbedo() const;
  void setAlbedo(Color c);

  Color mix(const Color &color) const override;
  Ray reflect(const Ray &ray, const Intersection &inter) const override;

private:
  Color albedo;
};
