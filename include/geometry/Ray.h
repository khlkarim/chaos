#pragma once

#include "geometry/Vector.h"

class Ray {
public:
  enum Type {
    NONE,
    REFLECTED,
    REFRACTED,
  };

  Ray() = default;
  Ray(Vec3 o, Vec3 d) : origin(o), direction(d) {}
  Ray(Vec3 o, Vec3 d, Type t) : origin(o), direction(d), type(t) {}

  Vec3 getOrigin() const;
  void setOrigin(Vec3 o);

  Vec3 getDirection() const;
  void setDirection(Vec3 d);

  Color getColor() const;
  void setColor(Color c);

  Type getType() const;
  void setType(Type t);

  Vec3 at(float t) const;

private:
  Type type;
  Color color;
  Vec3 origin;
  Vec3 direction;
};
