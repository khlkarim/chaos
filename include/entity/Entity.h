#pragma once

#include <map>
#include <memory>
#include <vector>

#include "components/Component.h"

using EntityId = int;

class EntityManager {
public:
  static constexpr int MAX_ENTITIES = 1000;
  static constexpr EntityId NIL = 0;

  EntityManager();

  EntityId createEntity();
  void removeEntity(EntityId eId);

  template <typename T> bool has(EntityId eId);
  bool has(EntityId eId, Component::Type type);
  bool hasAll(EntityId eId, const std::vector<Component::Type> &types);

  template <typename T> std::shared_ptr<T> get(EntityId eId);
  std::shared_ptr<Component> get(EntityId eId, Component::Type type);
  std::vector<std::shared_ptr<Component>> getAll(EntityId eId);

  void set(EntityId eId, std::shared_ptr<Component> component);
  void setAll(EntityId eId, const std::vector<std::shared_ptr<Component>> &components);

  template <typename T> void remove(EntityId eId);
  void remove(EntityId eId, Component::Type type);

  class Iterator {
  public:
    Iterator(EntityManager &em) : em(em) {}

    EntityId get() const;
    EntityId next();
    bool hasNext() const;

  private:
    EntityManager &em;
    EntityId curr = NIL;
  };

  Iterator createIterator();

private:
  std::vector<bool> used;
  std::map<Component::Type, std::vector<std::shared_ptr<Component>>> components;
};

template <typename T> bool EntityManager::has(EntityId eId) { return has(eId, T::TYPE); }
template <typename T> void EntityManager::remove(EntityId eId) { return remove(eId, T::TYPE); }
template <typename T> std::shared_ptr<T> EntityManager::get(EntityId eId) {
  return std::dynamic_pointer_cast<T>(get(eId, T::TYPE));
}
