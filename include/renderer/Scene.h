#pragma once

#include "geometry/Ray.h"
#include "renderer/Camera.h"

class Scene {
public:
  Scene() = default;
  explicit Scene(Camera c);

  Camera &getCamera();
  const Camera &getCamera() const;
  void setCamera(Camera camera);

  Color getColor(const Ray &r) const;

private:
  Camera camera;
};
