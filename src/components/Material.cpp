#include "materials/Dielectric.h"
#include "components/Hierarchy.h"
#include "components/Transform.h"

Component::Type Material::getType() const { return TYPE; }

Color Material::processLights(Scene &scene, Intersection &inter) const {
  auto emitted = COLOR_BLACK;
  auto lights = scene.getLights();
  auto &em = scene.getEntityManager();

  if (em.has<Hierarchy>(lights)) {
    auto hierarchy = em.get<Hierarchy>(lights);
    auto &children = hierarchy->getChildren();

    for (auto light : children) {
      if (em.has<Transform>(light)) {
        auto transform = em.get<Transform>(light);

        auto lightPos = transform->getPosition();
        auto origin = inter.getReflectionOrigin();
        auto direction = normalize(lightPos - origin);
        auto lightT = (lightPos - origin).length();

        Ray shadowRay(origin, direction);
        auto shadowInter = scene.intersect(shadowRay);
        auto hitMaterial = em.get<Material>(shadowInter.getEntity());
        auto isDielectric = std::dynamic_pointer_cast<Dielectric>(hitMaterial) != nullptr;

        if (shadowInter.getT() == -1 || shadowInter.getT() >= lightT || isDielectric) {
          emitted += processLight(scene, inter, light);
        }
      }
    }
  }

  return emitted;
}
