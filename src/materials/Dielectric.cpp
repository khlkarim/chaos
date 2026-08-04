#include <cmath>

#include "utils/math.h"
#include "materials/Dielectric.h"

float Dielectric::getRefractiveIndex() const { return refractiveIndex; }
void Dielectric::setRefractiveIndex(float n) { refractiveIndex = n; }

bool Dielectric::scatter(const Ray &ray, const Intersection &inter, Ray &scattered) const {
  Vec3 dir = normalize(ray.getDirection());
  float ri = inter.isFrontFace ? 1 / refractiveIndex : refractiveIndex;

  float a = std::fmin(-dot(dir, inter.normal), 1);
  float b = std::sqrt(1 - a * a);

  if (ri * b > 1.0 || getReflectance(a) > getRandomFLoat()) {
    scattered.setOrigin(ray.at(inter.t - EPSILON));
    scattered.setDirection(dir.reflect(inter.normal));
  } else {
    scattered.setOrigin(ray.at(inter.t + EPSILON));
    scattered.setDirection(dir.refract(inter.normal, ri));
  }

  return true;
}

Color Dielectric::emit(Scene &scene, const Ray &ray, const Intersection &inter, const Color &scattered) const {
  return scattered;
}

float Dielectric::getReflectance(float a) const {
  float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
  r0 = r0 * r0;
  return r0 + (1 - r0) * std::pow((1 - a), 5);
}
