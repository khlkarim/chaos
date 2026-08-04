#include "components/Transform.h"

Component::Type Transform::getType() const { return TYPE; }

Vec3 Transform::getPosition() const { return position; }
void Transform::setPosition(Vec3 p) { position = p; }

Vec3 Transform::getRotation() const { return rotation; }
void Transform::setRotation(Vec3 r) { rotation = r; }

Vec3 Transform::getScale() const { return scale; }
void Transform::setScale(Vec3 s) { scale = s; }

Vec3 Transform::apply(Vec3 v) const {
  v *= scale;
  v = v.rotate(rotation);
  v += position;
  return v;
}
