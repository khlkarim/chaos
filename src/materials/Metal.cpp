#include <cmath>

#include "materials/Metal.h"

float Metal::getFuzz() const { return fuzz; }
void Metal::setFuzz(float f) { fuzz = f; }

std::shared_ptr<Texture> Metal::getTexture() { return texture; }
void Metal::setTexture(std::shared_ptr<Texture> tex) { texture = tex; }

void Metal::scatter(Intersection &inter) const {
  Vec3 normal = getNormal(inter);
  Vec3 rand = Vec3::getRandomUnitSphere();

  auto &ray = inter.getIncidentRay();
  Vec3 rayDir = ray.getDirection();

  Vec3 origin = inter.getReflectionOrigin();
  Vec3 direction = normalize(rayDir.reflect(normal) + fuzz * rand);
  Ray reflected(origin, direction, Ray::REFLECTED);

  inter.setScatteredRays({reflected});
}

void Metal::emit(Scene &scene, Intersection &inter) const {
  Color emitted = COLOR_BLACK;
  auto &ray = inter.getIncidentRay();
  auto &scattered = inter.getScatteredRays();

  for (auto &r : scattered) {
    if (r.getType() == Ray::REFLECTED) {
      emitted += r.getColor();
    }
  }

  emitted += processLights(scene, inter);
  ray.setColor(emitted * texture->at(inter.getTexCoords()));
}

Color Metal::processLight(Scene &scene, Intersection &inter, Intersection &lightInter) const {
  Vec3 normal = getNormal(inter);
  auto &ray = inter.getIncidentRay();
  auto &lightRay = lightInter.getIncidentRay();

  auto lightColor = lightRay.getColor();
  auto reflectionDir = ray.getDirection().reflect(normal);
  float specular = std::pow(std::fmax(dot(reflectionDir, lightRay.getDirection()), 0.0), 100 * (1 - fuzz));

  return lightColor * specular;
}
