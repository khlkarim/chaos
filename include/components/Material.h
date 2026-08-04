#pragma once

#include "geometry/Ray.h"
#include "renderer/Scene.h"
#include "components/Component.h"
#include "geometry/Intersection.h"

class Material : public Component {
public:
  static const Component::Type TYPE = Component::Type::MATERIAL;
  Type getType() const override;

  virtual bool scatter(const Ray &ray, const Intersection &inter, Ray &scattered) const = 0;
  virtual Color emit(Scene &scene, const Ray &ray, const Intersection &inter, const Color &scattered) const = 0;
};
