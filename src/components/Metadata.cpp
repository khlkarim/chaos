#include "components/Metadata.h"

Component::Type Metadata::getType() const { return TYPE; }

std::string Metadata::getName() const { return name; }
void Metadata::setName(std::string n) { name = n; }

bool Metadata::getIsVisible() const { return isVisible; }
void Metadata::setIsVisible(bool v) { isVisible = v; }
