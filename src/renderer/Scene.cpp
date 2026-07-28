#include <memory>

#include "components/SDF.h"
#include "components/Mesh.h"
#include "components/Material.h"
#include "components/Transform.h"

#include "renderer/Scene.h"

Scene::Scene(Camera c) : camera(c) {}

Camera &Scene::getCamera() { return camera; }
const Camera &Scene::getCamera() const { return camera; }
void Scene::setCamera(Camera c) { camera = c; }

EntityManager &Scene::getEntityManager() { return em; }
const EntityManager &Scene::getEntityManager() const { return em; }
void Scene::setEntityManager(EntityManager em) { this->em = em; }

std::shared_ptr<Skybox> Scene::getSkybox() { return skybox; }
void Scene::setSkybox(std::shared_ptr<Skybox> s) { skybox = s; }

Color Scene::getColor(const Ray &ray, int depth) {
  if (depth == 0) {
    return COLOR_BLACK;
  }

  Intersection inter = intersect(ray);

  if (inter.t > 0 && em.has<Material>(inter.eId)) {
    auto mat = em.get<Material>(inter.eId);
    auto reflected = mat->reflect(ray, inter);
    return mat->mix(getColor(reflected, depth - 1));
  } else if (skybox != nullptr) {
    return skybox->getColor(ray);
  }

  return COLOR_WHITE;
}

Intersection Scene::intersect(const Ray &ray) {
  EntityId curr;
  Intersection inter, currInter;
  auto it = em.createIterator();

  while (it.hasNext()) {
    curr = it.next();

    if (em.has<SDF>(curr)) {
      auto sdf = em.get<SDF>(curr);

      if (em.has<Transform>(curr)) {
        auto transform = em.get<Transform>(curr);
        currInter = sdf->intersect(ray, *transform);
      } else {
        currInter = sdf->intersect(ray);
      }
    } else if (em.has<Mesh>(curr)) {
      auto mesh = em.get<Mesh>(curr);

      if (em.has<Transform>(curr)) {
        auto transform = em.get<Transform>(curr);
        currInter = mesh->intersect(ray, *transform);
      } else {
        currInter = mesh->intersect(ray);
      }
    }

    if (currInter.t > 0 && (inter.t == -1 || currInter.t < inter.t)) {
      inter = currInter;
      inter.eId = curr;
    }
  }

  return inter;
}
