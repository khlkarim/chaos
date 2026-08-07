#include "geometry/Intersection.h"

float Intersection::getReflectionBias() const { return reflectionBias; }
void Intersection::setReflectionBias(float f) { reflectionBias = f; }

float Intersection::getRefractionBias() const { return refractionBias; }
void Intersection::setRefractionBias(float f) { refractionBias = f; }

Vec3 Intersection::getIntersectionOrigin() const { return incident.at(t); }
Vec3 Intersection::getReflectionOrigin() const { return incident.at(t - reflectionBias); }
Vec3 Intersection::getRefractionOrigin() const { return incident.at(t + refractionBias); }

Ray &Intersection::getIncidentRay() { return incident; }
const Ray &Intersection::getIncidentRay() const { return incident; }

void Intersection::setIncidentRay(Ray r) {
  incident.setOrigin(r.getOrigin());
  incident.setDirection(r.getDirection());
}

std::vector<Ray> &Intersection::getScatteredRays() { return scattered; }
const std::vector<Ray> &Intersection::getScatteredRays() const { return scattered; }
void Intersection::setScatteredRays(const std::vector<Ray> &r) { scattered = r; }

float Intersection::getT() const { return t; }
void Intersection::setT(float f) { t = f; }

void Intersection::setNormal(Vec3 outwardNormal, Vec3 rayDir) {
  isFrontFace = dot(outwardNormal, rayDir) < 0;
  normal = isFrontFace ? outwardNormal : -outwardNormal;
}

void Intersection::setTriNormal(Vec3 outwardNormal, Vec3 rayDir) {
  isFrontFace = dot(outwardNormal, rayDir) < 0;
  triNormal = isFrontFace ? outwardNormal : -outwardNormal;
}

Vec3 Intersection::getNormal() const { return normal; }
Vec3 Intersection::getTriNormal() const { return triNormal; }
bool Intersection::getIsFrontFace() const { return isFrontFace; }

Vec2 Intersection::getTexCoords() const { return texCoords; }
void Intersection::setTexCoords(Vec2 t) { texCoords = t; }

EntityId Intersection::getEntity() const { return eId; }
void Intersection::setEntity(EntityId e) { eId = e; }
