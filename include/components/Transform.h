#pragma once

#include "Component.h"
#include "geometry/Vector.h"

class Transform : public Component {
public:
  static const Component::Type TYPE = Component::Type::TRANSFORM;
  Type getType() const override;

  Transform() = default;
  Transform(Vec3 position, Vec3 scale = Vec3(1)) : position(position), scale(scale) {}

  Vec3 getPosition() const;
  void setPosition(Vec3 p);

  Vec3 getScale() const;
  void setScale(Vec3 s);

private:
  Vec3 position = Vec3(0);
  Vec3 scale = Vec3(1);
};
