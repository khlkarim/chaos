#include "utils/math.h"
#include "materials/Metal.h"

float Metal::getFuzz() const { return fuzz; }
void Metal::setFuzz(float f) { fuzz = f; }

std::shared_ptr<Texture> Metal::getTexture() { return texture; }
void Metal::setTexture(std::shared_ptr<Texture> tex) { texture = tex; }

bool Metal::scatter(const Ray &ray, const Intersection &inter, Ray &scattered) const {
  Vec3 dir = ray.getDirection();
  Vec3 rand = Vec3::getRandomUnitSphere();
  scattered.setOrigin(ray.at(inter.t - EPSILON));
  scattered.setDirection(normalize(dir.reflect(inter.normal) + fuzz * rand));
  return true;
}

Color Metal::emit(Scene &scene, const Ray &ray, const Intersection &inter, const Color &scattered) const {
  return scattered * texture->at(inter.texCoords);
}
