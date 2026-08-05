#include <cmath>
#include "materials/Dielectric.h"

float Dielectric::getRefractiveIndex() const { return refractiveIndex; }
void Dielectric::setRefractiveIndex(float n) { refractiveIndex = n; }

void Dielectric::scatter(Intersection &inter) const {
  auto &ray = inter.getIncidentRay();
  auto &scattered = inter.getScatteredRays();

  Vec3 normal = inter.getNormal();
  Vec3 rayDir = ray.getDirection();

  float ri = inter.getIsFrontFace() ? 1 / refractiveIndex : refractiveIndex;
  float a = std::fmin(-dot(rayDir, normal), 1);
  float b = std::sqrt(1 - a * a);

  Vec3 origin = inter.getReflectionOrigin();
  Vec3 direction = rayDir.reflect(normal);
  Ray reflected(origin, direction, Ray::REFLECTED);
  scattered.push_back(reflected);

  if (ri * b <= 1.0) {
    origin = inter.getRefractionOrigin();
    direction = rayDir.refract(normal, ri);
    Ray refracted(origin, direction, Ray::REFRACTED);
    scattered.push_back(refracted);
  }
}

void Dielectric::emit(Scene &scene, Intersection &inter) const {
  Color emitted = COLOR_BLACK;
  auto &ray = inter.getIncidentRay();
  auto &scattered = inter.getScatteredRays();

  Color reflectedColor = COLOR_BLACK;
  Color refractedColor = COLOR_BLACK;

  for (auto r : scattered) {
    if (r.getType() == Ray::REFLECTED) {
      reflectedColor += r.getColor();
    } else if (r.getType() == Ray::REFRACTED) {
      refractedColor += r.getColor();
    }
  }

  float a = std::fmin(dot(-ray.getDirection(), inter.getNormal()), 1);
  float reflectance = 0.5 * std::pow(1 - a, 5);
  emitted = reflectance * reflectedColor + (1 - reflectance) * refractedColor;
  ray.setColor(emitted);
}
