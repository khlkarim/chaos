#include <memory>
#include <vector>
#include <iostream>

#include "utils/math.h"
#include "entity/Entity.h"
#include "components/Metadata.h"

constexpr int REMOVE = 100;
constexpr int OVERFLOW = 10;

void report(const std::vector<EntityId> &entities, EntityManager &em);

int main() {
  EntityManager em;

  int n = EntityManager::MAX_ENTITIES + OVERFLOW;
  std::vector<EntityId> entities(n);

  for (int i = 0; i < n; i++) {
    entities[i] = em.createEntity();
    std::string name = "Entity " + std::to_string(i);
    auto m = std::make_shared<Metadata>(name, i % 2);
    em.set(entities[i], m);
  }

  report(entities, em);

  for (int i = 0; i < REMOVE; i++) {
    int j = getRandomInt(0, n - 1);

    if (j % 2) {
      em.removeEntity(entities[j]);
      entities[j] = EntityManager::NIL;
    } else {
      auto m = em.get<Metadata>(entities[j]);
      m->setIsVisible(false);
    }
  }

  report(entities, em);
}

void report(const std::vector<EntityId> &entities, EntityManager &em) {
  int nbNIL = 0;
  int nbVisible = 0;

  for (auto e : entities) {
    if (e == EntityManager::NIL) {
      nbNIL++;
    } else {
      auto m = em.get<Metadata>(e);
      nbVisible += m->getIsVisible();
    }
  }

  std::cout << "Number of NILs: " << nbNIL << std::endl;
  std::cout << "Number of Visible entities: " << nbVisible << std::endl;
  std::cout << std::endl;
}
