#include <cmath>

#include "renderer/Scene.h"

Scene::Scene(Camera c) : camera(c) {}

Camera &Scene::getCamera() { return camera; }
const Camera &Scene::getCamera() const { return camera; }
void Scene::setCamera(Camera c) { camera = c; }

Color Scene::getColor(const Ray &ray) const {
  Vec3 d = ray.getDirection();

  Vec3 up = camera.getUp();
  Vec3 front = camera.getFront();
  Vec3 right = camera.getRight();

  float r = std::abs(dot(up, d));
  float g = std::abs(dot(right, d));
  float b = std::abs(dot(front, d));

  return {r, g, b, 1};
}
