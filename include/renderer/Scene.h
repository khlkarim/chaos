#pragma once

#include <memory>

#include "skybox/Sky.h"
#include "entity/Entity.h"
#include "renderer/Camera.h"
#include "geometry/Intersection.h"

class Scene {
public:
  Scene() = default;
  explicit Scene(Camera c);

  Camera &getCamera();
  const Camera &getCamera() const;
  void setCamera(Camera camera);

  EntityManager &getEntityManager();
  const EntityManager &getEntityManager() const;
  void setEntityManager(EntityManager em);

  std::shared_ptr<Skybox> getSkybox();
  void setSkybox(std::shared_ptr<Skybox> s);

  Intersection intersect(const Ray &ray);
  Color getColor(const Ray &ray, int depth);

private:
  Camera camera;
  EntityManager em;
  std::shared_ptr<Skybox> skybox = std::make_shared<Sky>();
};
