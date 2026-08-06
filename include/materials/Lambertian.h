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

  void scatter(Intersection &inter) const override;
  void emit(Scene &scene, Intersection &inter) const override;

protected:
  Color processLight(Scene &scene, Intersection &inter, EntityId light) const override;

private:
  std::shared_ptr<Texture> texture;
};
