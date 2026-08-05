#include "geometry/Ray.h"

Ray::Type Ray::getType() const { return type; }
void Ray::setType(Type t) { type = t; }

Color Ray::getColor() const { return color; }
void Ray::setColor(Color c) { color = c; }

Vec3 Ray::getOrigin() const { return origin; }
void Ray::setOrigin(Vec3 o) { origin = o; }

Vec3 Ray::getDirection() const { return direction; }
void Ray::setDirection(Vec3 d) { direction = d; }

Vec3 Ray::at(float t) const { return origin + t * direction; }
