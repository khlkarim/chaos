#pragma once

#include "geometry/Vector.h"

class Camera {
public:
  float getFov() const;
  void setFov(float f);

  float getNearPlane() const;
  void setNearPlane(float f);

  float getYaw() const;
  void setYaw(float f);

  float getPitch() const;
  void setPitch(float f);

  Vec3 getPosition() const;
  void setPosition(Vec3 v);

  Vec3 getUp() const;
  void setUp(Vec3 v);

  Vec3 getRight() const;
  void setRight(Vec3 v);

  Vec3 getFront() const;
  void setFront(Vec3 pos);

private:
  float fov = 45;
  float nearPlane = 1;

  float yaw = 0;
  float pitch = 0;
  Vec3 worldUp = {0, 1, 0};
  Vec3 position = {0, 0, 0};
};
