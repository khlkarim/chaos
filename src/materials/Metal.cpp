#include <cmath>

#include "materials/Metal.h"
#include "components/Transform.h"

float Metal::getFuzz() const { return fuzz; }
void Metal::setFuzz(float f) { fuzz = f; }

std::shared_ptr<Texture> Metal::getTexture() { return texture; }
void Metal::setTexture(std::shared_ptr<Texture> tex) { texture = tex; }

void Metal::scatter(Intersection &inter) const {
  Vec3 rand = Vec3::getRandomUnitSphere();
  auto &ray = inter.getIncidentRay();
  Vec3 rayDir = ray.getDirection();

  Vec3 origin = inter.getReflectionOrigin();
  Vec3 direction = normalize(rayDir.reflect(inter.getNormal()) + fuzz * rand);
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

Color Metal::processLight(Scene &scene, Intersection &inter, EntityId light) const {
  auto &ray = inter.getIncidentRay();
  auto &em = scene.getEntityManager();

  auto material = em.get<Material>(light);
  auto transform = em.get<Transform>(light);

  auto lightPos = transform->getPosition();
  auto origin = inter.getReflectionOrigin();
  auto direction = normalize(lightPos - origin);
  auto lightT = (lightPos - origin).length();

  Intersection shadowInter;
  shadowInter.setT(lightT);
  shadowInter.setEntity(light);
  shadowInter.setIncidentRay(Ray(origin, direction));
  material->emit(scene, shadowInter);

  auto lightColor = shadowInter.getIncidentRay().getColor();
  auto reflectionDir = ray.getDirection().reflect(inter.getNormal());
  float specular = std::pow(std::fmax(dot(reflectionDir, direction), 0.0), 100 * (1 - fuzz));
  return lightColor * specular;
}
