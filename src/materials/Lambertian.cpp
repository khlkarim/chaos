#include <cmath>
#include <memory>

#include "components/Material.h"
#include "components/Component.h"
#include "components/Hierarchy.h"
#include "components/Transform.h"
#include "materials/Dielectric.h"
#include "materials/Lambertian.h"

std::shared_ptr<Texture> Lambertian::getTexture() { return texture; }
void Lambertian::setTexture(std::shared_ptr<Texture> tex) { texture = tex; }

void Lambertian::scatter(Intersection &inter) const {
  Vec3 rand = Vec3::getRandomUnitSphere();

  Vec3 origin = inter.getReflectionOrigin();
  Vec3 direction = normalize(inter.getNormal() + rand);
  Ray reflected(origin, direction, Ray::REFLECTED);

  inter.setScatteredRays({reflected});
}

void Lambertian::emit(Scene &scene, Intersection &inter) const {
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
          float diffuse = std::fabs(dot(inter.getNormal(), direction));
          emitted += lightColor * diffuse;
        }
      }
    }
  }

  ray.setColor(emitted * texture->at(inter.getTexCoords()));
}
