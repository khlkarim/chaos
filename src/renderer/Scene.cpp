#include <memory>

#include "components/Geometry.h"
#include "components/Hierarchy.h"
#include "components/Material.h"
#include "components/Transform.h"

#include "renderer/Scene.h"

Scene::Scene() { initLights(); }
Scene::Scene(Camera c) : camera(c) { initLights(); }

Camera &Scene::getCamera() { return camera; }
const Camera &Scene::getCamera() const { return camera; }
void Scene::setCamera(Camera c) { camera = c; }

EntityManager &Scene::getEntityManager() { return em; }
const EntityManager &Scene::getEntityManager() const { return em; }
void Scene::setEntityManager(EntityManager em) { this->em = em; }

EntityId Scene::getLights() const { return lights; }
void Scene::setLights(EntityId l) { lights = l; }

std::shared_ptr<Skybox> Scene::getSkybox() { return skybox; }
void Scene::setSkybox(std::shared_ptr<Skybox> s) { skybox = s; }

void Scene::setColor(Ray &ray, int depth) {
  if (depth == 0) {
    ray.setColor(COLOR_BLACK);
    return;
  }

  Color color = COLOR_MAGENTA;
  Intersection inter = intersect(ray);

  if (inter.getT() > 0 && em.has<Material>(inter.getEntity())) {
    auto mat = em.get<Material>(inter.getEntity());

    mat->scatter(inter);
    for (auto &r : inter.getScatteredRays()) {
      setColor(r, depth - 1);
    }
    mat->emit(*this, inter);

    color = inter.getIncidentRay().getColor();
  } else if (skybox != nullptr) {
    color = skybox->getColor(ray);
  }

  ray.setColor(color);
}

Intersection Scene::intersect(const Ray &ray) {
  EntityId curr;
  Intersection inter, currInter;
  auto it = em.createIterator();

  while (it.hasNext()) {
    curr = it.next();
    if (!em.has<Geometry>(curr)) {
      continue;
    }

    auto geometry = em.get<Geometry>(curr);

    if (em.has<Transform>(curr)) {
      auto transform = em.get<Transform>(curr);
      currInter = geometry->intersect(ray, *transform);
    } else {
      currInter = geometry->intersect(ray);
    }

    if (currInter.getT() > 0 && (inter.getT() == -1 || currInter.getT() < inter.getT())) {
      inter = currInter;
      inter.setEntity(curr);
    }
  }

  return inter;
}

void Scene::initLights() {
  lights = em.createEntity();
  auto hierarchy = std::make_shared<Hierarchy>();
  em.set(lights, hierarchy);
}
