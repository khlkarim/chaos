#pragma once

#include <memory>

#include "textures/SolidColor.h"
#include "components/Material.h"

class Emissive : public Material {
public:
  Emissive(Color albedo = COLOR_WHITE) : texture(std::make_shared<SolidColor>(albedo)) {}
  Emissive(std::shared_ptr<Texture> texture) : texture(texture) {}

  std::shared_ptr<Texture> getTexture();
  void setTexture(std::shared_ptr<Texture> tex);

  virtual void scatter(Intersection &inter) const override;
  virtual void emit(Scene &scene, Intersection &inter) const override;

private:
  std::shared_ptr<Texture> texture;
};
