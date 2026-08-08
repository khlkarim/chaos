#pragma once

#include "Component.h"
#include "geometry/Vector.h"

class Transform : public Component {
public:
  static const Component::Type TYPE = Component::Type::TRANSFORM;
  virtual Type getType() const override;

  Transform() = default;
  Transform(Vec3 p, Vec3 s = 1, Vec3 r = 0) : position(p), scale(s), rotation(r) {}

  Vec3 getPosition() const;
  void setPosition(Vec3 p);

  Vec3 getRotation() const;
  void setRotation(Vec3 r);

  Vec3 getScale() const;
  void setScale(Vec3 s);

  Vec3 apply(Vec3 v) const;

private:
  Vec3 position;
  Vec3 rotation;
  Vec3 scale = Vec3(1);
};
