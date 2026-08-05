#include <memory>
#include "materials/Emissive.h"

std::shared_ptr<Texture> Emissive::getTexture() { return texture; }
void Emissive::setTexture(std::shared_ptr<Texture> tex) { texture = tex; }

void Emissive::scatter(Intersection &inter) const {}

void Emissive::emit(Scene &scene, Intersection &inter) const {
  auto &ray = inter.getIncidentRay();
  ray.setColor(texture->at(inter.getTexCoords()));
}
