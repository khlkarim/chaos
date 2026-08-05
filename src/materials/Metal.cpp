#include <cmath>
#include "materials/Metal.h"
#include "components/Hierarchy.h"
#include "components/Transform.h"
#include "materials/Dielectric.h"

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

  auto lights = scene.getLights();
  auto &em = scene.getEntityManager();

  for (auto &r : scattered) {
    if (r.getType() == Ray::REFLECTED) {
      emitted += r.getColor();
    }
  }

  if (em.has<Hierarchy>(lights)) {
    auto hierarchy = em.get<Hierarchy>(lights);
    auto &children = hierarchy->getChildren();

    for (auto light : children) {
      if (em.hasAll(light, {Component::TRANSFORM, Component::MATERIAL})) {
        auto material = em.get<Material>(light);
        auto transform = em.get<Transform>(light);

        auto lightPos = transform->getPosition();
        auto origin = inter.getReflectionOrigin();
        auto direction = normalize(lightPos - origin);
        auto lightT = (lightPos - origin).length();

        Ray shadowRay(origin, direction);
        auto shadowInter = scene.intersect(shadowRay);
        material->emit(scene, shadowInter);

        auto lightColor = shadowInter.getIncidentRay().getColor();
        auto hitMaterial = em.get<Material>(shadowInter.getEntity());
        auto isDielectric = std::dynamic_pointer_cast<Dielectric>(hitMaterial) != nullptr;

        if (shadowInter.getT() == -1 || shadowInter.getT() >= lightT || isDielectric) {
          for (auto &r : scattered) {
            if (r.getType() == Ray::REFLECTED) {
              float specular = std::pow(std::fmax(dot(r.getDirection(), direction), 0.0), 100 * (1 - fuzz));
              emitted += lightColor * specular;
            }
          }
        }
      }
    }
  }

  ray.setColor(emitted * texture->at(inter.getTexCoords()));
}
