#pragma once

#include <memory>

#include "textures/SolidColor.h"
#include "components/Material.h"

class Lambertian : public Material {
public:
  Lambertian(Color albedo = COLOR_WHITE) : texture(std::make_shared<SolidColor>(albedo)) {}
  Lambertian(std::shared_ptr<Texture> texture) : texture(texture) {}

  std::shared_ptr<Texture> getTexture();
  void setTexture(std::shared_ptr<Texture> tex);

  bool scatter(const Ray &ray, const Intersection &inter, Ray &scattered) const override;
  Color emit(Scene &scene, const Ray &ray, const Intersection &inter, const Color &scattered) const override;

private:
  std::shared_ptr<Texture> texture;
};
