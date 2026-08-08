#include <cmath>
#include <memory>

#include "materials/Lambertian.h"

std::shared_ptr<Texture> Lambertian::getTexture() { return texture; }
void Lambertian::setTexture(std::shared_ptr<Texture> tex) { texture = tex; }

void Lambertian::scatter(Intersection &inter) const {
  Vec3 normal = getNormal(inter);
  Vec3 rand = Vec3::getRandomUnitSphere();

  Vec3 origin = inter.getReflectionOrigin();
  Vec3 direction = normalize(normal + rand);
  Ray reflected(origin, direction, Ray::REFLECTED);

  inter.setScatteredRays({reflected});
}

void Lambertian::emit(Scene &scene, Intersection &inter) const {
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

Color Lambertian::processLight(Scene &scene, Intersection &inter, Intersection &lightInter) const {
  Vec3 normal = getNormal(inter);
  auto &incident = lightInter.getIncidentRay();

  auto lightColor = incident.getColor();
  auto direction = incident.getDirection();
  float diffuse = std::fmin(dot(normal, direction), 1);

  return lightColor * diffuse;
}
