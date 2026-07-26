#pragma once

#include "geometry/Ray.h"
#include "components/Component.h"
#include "geometry/Intersection.h"

class Material : public Component {
public:
  static const Component::Type TYPE = Component::Type::MATERIAL;
  Type getType() const override;

  virtual Color mix(const Color &color) const = 0;
  virtual Ray reflect(const Ray &ray, const Intersection &inter) const = 0;
};
