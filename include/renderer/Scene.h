#pragma once

#include <memory>
#include <vector>

#include "renderer/Camera.h"
#include "renderer/Entity.h"

class Scene {
public:
  std::vector<std::shared_ptr<Entity>> entities;

  Scene() = default;
  explicit Scene(Camera c);

  Camera &getCamera();
  const Camera &getCamera() const;
  void setCamera(Camera camera);

  Color getColor(const Ray &r, int depth) const;

private:
  Camera camera;
};
