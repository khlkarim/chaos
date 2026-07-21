#include "renderer/Scene.h"
#include "utils/math.h"

Scene::Scene(Camera c) : camera(c) {}

Camera &Scene::getCamera() { return camera; }
const Camera &Scene::getCamera() const { return camera; }
void Scene::setCamera(Camera c) { camera = c; }

Color getBackgroundColor(const Ray &ray) {
  Vec3 d = ray.getDirection();
  auto a = 0.5 * (d.y + 1.0);
  Color c1(1), c2(0.5, 0.7, 1.0, 1.0);
  return (1 - a) * c1 + a * c2;
}

Color Scene::getColor(const Ray &ray, int depth) const {
  if (depth == 0) {
    return Color(0, 0, 0, 1);
  }

  int closestIdx = -1;
  Intersection closestInter;

  for (int i = 0; i < entities.size(); i++) {
    Intersection inter = entities[i]->intersect(ray);

    if (inter.t >= 0 && (closestIdx == -1 || inter.t < closestInter.t)) {
      closestIdx = i;
      closestInter = inter;
    }
  }

  if (closestIdx != -1) {
    Vec3 direction = Vec3::getRandomUnitSphere();
    Vec3 origin = ray.getOrigin() + (closestInter.t - EPSILON) * ray.getDirection();

    if (dot(closestInter.normal, direction) < 0) {
      direction *= -1;
    }

    Ray scattered(origin, direction);
    Color scatteredColor = 0.5 * getColor(scattered, depth - 1);
    scatteredColor.w = 1;

    return scatteredColor;
  } else {
    return getBackgroundColor(ray);
  }
}
