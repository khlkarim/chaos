#pragma once

#include "textures/SolidColor.h"
#include "components/Material.h"

class Metal : public Material {
public:
  Metal(Color albedo = COLOR_WHITE, float f = 0) : texture(std::make_shared<SolidColor>(albedo)), fuzz(f) {}
  Metal(std::shared_ptr<Texture> texture, float f = 0) : texture(texture), fuzz(f) {}

  float getFuzz() const;
  void setFuzz(float f);

  std::shared_ptr<Texture> getTexture();
  void setTexture(std::shared_ptr<Texture> tex);

  virtual void scatter(Intersection &inter) const override;
  virtual void emit(Scene &scene, Intersection &inter) const override;

protected:
  virtual Color processLight(Scene &scene, Intersection &inter, Intersection &lightInter) const override;

private:
  float fuzz;
  std::shared_ptr<Texture> texture;
};
