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

  virtual void scatter(Intersection &inter) const override;
  virtual void emit(Scene &scene, Intersection &inter) const override;

protected:
  virtual Color processLight(Scene &scene, Intersection &inter, Intersection &lightInter) const override;

private:
  std::shared_ptr<Texture> texture;
};
