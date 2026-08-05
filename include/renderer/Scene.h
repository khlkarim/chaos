#pragma once

#include <memory>

#include "skybox/Sky.h"
#include "entity/Entity.h"
#include "renderer/Camera.h"
#include "geometry/Intersection.h"

class Scene {
public:
  Scene();
  explicit Scene(Camera c);

  Camera &getCamera();
  const Camera &getCamera() const;
  void setCamera(Camera camera);

  EntityManager &getEntityManager();
  const EntityManager &getEntityManager() const;
  void setEntityManager(EntityManager em);

  EntityId getLights() const;
  void setLights(EntityId l);

  std::shared_ptr<Skybox> getSkybox();
  void setSkybox(std::shared_ptr<Skybox> s);

  void setColor(Ray &ray, int depth);
  Intersection intersect(const Ray &ray);

private:
  void initLights();

  Camera camera;
  EntityManager em;
  EntityId lights = EntityManager::NIL;
  std::shared_ptr<Skybox> skybox = std::make_shared<Sky>();
};
