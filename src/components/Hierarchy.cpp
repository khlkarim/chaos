#include "components/Hierarchy.h"

Component::Type Hierarchy::getType() const { return TYPE; }

void Hierarchy::add(EntityId child) { children.insert(child); }
void Hierarchy::remove(EntityId child) { children.erase(child); }

std::set<EntityId> &Hierarchy::getChildren() { return children; }
const std::set<EntityId> &Hierarchy::getChildren() const { return children; }
void Hierarchy::setChildren(const std::set<EntityId> &c) { children = c; }
