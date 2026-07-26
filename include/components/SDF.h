#pragma once

#include "geometry/Ray.h"
#include "components/Transform.h"
#include "geometry/Intersection.h"

class SDF : public Component {
public:
  static const Component::Type TYPE = Component::Type::SDF;
  Type getType() const override;

  virtual Intersection intersect(const Ray &ray, const Transform &transform = Transform()) const = 0;
};
