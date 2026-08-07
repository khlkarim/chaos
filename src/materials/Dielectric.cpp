#include <cmath>
#include "materials/Dielectric.h"

float Dielectric::getRefractiveIndex() const { return refractiveIndex; }
void Dielectric::setRefractiveIndex(float n) { refractiveIndex = n; }

void Dielectric::scatter(Intersection &inter) const {
  auto normal = getNormal(inter);
  auto &ray = inter.getIncidentRay();
  auto &scattered = inter.getScatteredRays();
  float ri = inter.getIsFrontFace() ? 1 / refractiveIndex : refractiveIndex;

  Vec3 origin, direction, rayDir = ray.getDirection();
  float cosine = clamp(-dot(rayDir, normal), 0, 1);
  float sine = std::sqrt(1 - cosine * cosine);

  origin = inter.getReflectionOrigin();
  direction = normalize(rayDir.reflect(normal));
  scattered.push_back(Ray(origin, direction, Ray::REFLECTED));

  if (ri * sine <= 1) {
    origin = inter.getRefractionOrigin();
    direction = normalize(rayDir.refract(normal, ri));
    scattered.push_back(Ray(origin, direction, Ray::REFRACTED));
  }
}

void Dielectric::emit(Scene &scene, Intersection &inter) const {
  auto normal = getNormal(inter);
  auto &ray = inter.getIncidentRay();
  auto &scattered = inter.getScatteredRays();
  float ri = inter.getIsFrontFace() ? 1 / refractiveIndex : refractiveIndex;

  Color emitted = COLOR_BLACK;
  Color reflectedColor = COLOR_BLACK;
  Color refractedColor = COLOR_BLACK;

  for (auto r : scattered) {
    if (r.getType() == Ray::REFLECTED) {
      reflectedColor += r.getColor();
    } else if (r.getType() == Ray::REFRACTED) {
      refractedColor += r.getColor();
    }
  }

  Vec3 rayDir = ray.getDirection();
  float cosine = clamp(dot(-rayDir, normal), 0, 1);
  float sine = std::sqrt(1 - cosine * cosine);

  if (ri * sine <= 1) {
    float reflectance = 0.5 * std::pow(1 - cosine, 5);
    emitted = reflectance * reflectedColor + (1 - reflectance) * refractedColor;
  } else {
    emitted = reflectedColor;
  }

  ray.setColor(emitted);
}
