#pragma once

#include "components/Transform.h"
#include "geometry/Intersection.h"

class Geometry : public Component {
public:
  static const Component::Type TYPE = Component::Type::GEOMETRY;
  Type getType() const override;

  virtual Intersection intersect(const Ray &ray, const Transform &transform = Transform()) const = 0;
};
