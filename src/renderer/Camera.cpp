#include <cmath>

#include "geometry/Vector.h"
#include "renderer/Camera.h"

#define PI 3.14159265359

float Camera::getFov() const { return fov; }
void Camera::setFov(float f) { fov = f; }

float Camera::getNearPlane() const { return nearPlane; }
void Camera::setNearPlane(float f) { nearPlane = f; }

float Camera::getYaw() const { return yaw; }
void Camera::setYaw(float f) { yaw = f; }

float Camera::getPitch() const { return pitch; }
void Camera::setPitch(float f) { pitch = f; }

Vec3 Camera::getPosition() const { return position; }
void Camera::setPosition(Vec3 v) { position = v; }

Vec3 Camera::getFront() const {
  float y = sin(pitch * PI / 180.);
  float z = -cos(yaw * PI / 180.) * cos(pitch * PI / 180.);
  float x = sin(yaw * PI / 180.) * cos(pitch * PI / 180.);
  return {x, y, z};
}

Vec3 Camera::getRight() const {
  Vec3 front = getFront();
  return normalize(cross(front, worldUp));
}

Vec3 Camera::getUp() const {
  Vec3 front = getFront();
  Vec3 right = getRight();
  return normalize(cross(right, front));
}
