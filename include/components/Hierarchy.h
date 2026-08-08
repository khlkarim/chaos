#pragma once

#include <set>

#include "entity/Entity.h"

class Hierarchy : public Component {
public:
  static const Component::Type TYPE = Component::Type::HIERARCHY;
  virtual Type getType() const override;

  void add(EntityId child);
  void remove(EntityId child);

  std::set<EntityId> &getChildren();
  const std::set<EntityId> &getChildren() const;
  void setChildren(const std::set<EntityId> &c);

private:
  std::set<EntityId> children;
};
