#include <vector>

#include "entity/Entity.h"

EntityManager::EntityManager() { used = std::vector<bool>(MAX_ENTITIES + 1, false); }

EntityId EntityManager::createEntity() {
  for (EntityId e = 1; e <= MAX_ENTITIES; e++) {
    if (!used[e]) {
      used[e] = true;
      return e;
    }
  }

  return NIL;
}

void EntityManager::removeEntity(EntityId eId) {
  if (eId <= NIL || eId > MAX_ENTITIES || !used[eId]) {
    return;
  }

  for (int i = 0; i < Component::Type::TYPE_COUNT; i++) {
    Component::Type type = static_cast<Component::Type>(i);
    remove(eId, type);
  }

  used[eId] = false;
}

bool EntityManager::has(EntityId eId, Component::Type type) {
  if (eId <= NIL || eId > MAX_ENTITIES || !used[eId]) {
    return false;
  }

  if (components[type].size() < eId + 1) {
    return false;
  }

  return components[type][eId] != nullptr;
}

bool EntityManager::hasAll(EntityId eId, const std::vector<Component::Type> &types) {
  for (auto t : types) {
    if (!has(eId, t)) {
      return false;
    }
  }

  return true;
}

std::vector<std::shared_ptr<Component>> EntityManager::getAll(EntityId eId) {
  if (eId <= NIL || eId > MAX_ENTITIES || !used[eId]) {
    return {};
  }

  std::vector<std::shared_ptr<Component>> res;

  for (int i = 0; i < Component::Type::TYPE_COUNT; i++) {
    Component::Type type = static_cast<Component::Type>(i);

    if (has(eId, type)) {
      res.push_back(get(eId, type));
    }
  }

  return res;
}

std::shared_ptr<Component> EntityManager::get(EntityId eId, Component::Type type) {
  if (!has(eId, type)) {
    return nullptr;
  }

  return components[type][eId];
}

void EntityManager::set(EntityId eId, std::shared_ptr<Component> component) {
  if (eId <= NIL || eId > MAX_ENTITIES || !used[eId] || component == nullptr) {
    return;
  }

  auto type = component->getType();
  auto &arr = components[type];

  while (arr.size() <= eId) {
    arr.push_back(nullptr);
  }

  arr[eId] = component;
}

void EntityManager::setAll(EntityId eId, const std::vector<std::shared_ptr<Component>> &components) {
  for (auto ptr : components) {
    set(eId, ptr);
  }
}

void EntityManager::remove(EntityId eId, Component::Type type) {
  if (!has(eId, type)) {
    return;
  }

  components[type][eId].reset();
}

EntityManager::Iterator EntityManager::createIterator() { return Iterator(*this); }

EntityId EntityManager::Iterator::next() {
  curr++;

  while (curr <= MAX_ENTITIES) {
    if (em.used[curr]) {
      return curr;
    }

    curr++;
  }

  curr = NIL;
  return curr;
}

bool EntityManager::Iterator::hasNext() const {
  EntityId eId = curr + 1;

  while (eId <= MAX_ENTITIES) {
    if (em.used[eId]) {
      return true;
    }

    eId++;
  }

  return false;
}

EntityId EntityManager::Iterator::get() const { return curr; }
