#include "utils/math.h"
#include "materials/Lambertian.h"

std::shared_ptr<Texture> Lambertian::getTexture() { return texture; }
void Lambertian::setTexture(std::shared_ptr<Texture> tex) { texture = tex; }

bool Lambertian::scatter(const Ray &ray, const Intersection &inter, Ray &scattered) const {
  Vec3 rand = Vec3::getRandomUnitSphere();
  scattered.setOrigin(ray.at(inter.t - EPSILON));
  scattered.setDirection(normalize(inter.normal + rand));
  return true;
}

Color Lambertian::emit(Scene &scene, const Ray &ray, const Intersection &inter, const Color &scattered) const {
  return scattered * texture->at(inter.texCoords);
}
