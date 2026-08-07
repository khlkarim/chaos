#pragma once

#include "renderer/Scene.h"

class Material : public Component {
public:
  static const Component::Type TYPE = Component::Type::MATERIAL;
  Type getType() const override;

  bool getSmoothShading() const;
  void setSmoothShading(bool s);
  Vec3 getNormal(const Intersection &inter) const;

  virtual void scatter(Intersection &inter) const = 0;
  virtual void emit(Scene &scene, Intersection &inter) const = 0;

protected:
  virtual Color processLights(Scene &scene, Intersection &inter) const;
  virtual Color processLight(Scene &scene, Intersection &inter, EntityId light) const { return 0; }

  bool smoothShading = true;
};
