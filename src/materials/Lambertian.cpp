#include <cmath>
#include <memory>

#include "components/Transform.h"
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

Color Lambertian::processLight(Scene &scene, Intersection &inter, EntityId light) const {
  Vec3 normal = getNormal(inter);
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
  float diffuse = std::fmin(dot(normal, direction), 1);
  return lightColor * diffuse;
}
