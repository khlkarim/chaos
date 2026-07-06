#include "geometry/Ray.h"

Vec3 Ray::getOrigin() const { return origin; }
void Ray::setOrigin(Vec3 o) { origin = o; }

Vec3 Ray::getDirection() const { return direction; }
void Ray::setDirection(Vec3 d) { direction = d; }
