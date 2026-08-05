#pragma once

#include "renderer/Scene.h"
#include "components/Component.h"
#include "geometry/Intersection.h"

class Material : public Component {
public:
  static const Component::Type TYPE = Component::Type::MATERIAL;
  Type getType() const override;

  virtual void scatter(Intersection &inter) const = 0;
  virtual void emit(Scene &scene, Intersection &inter) const = 0;
};
