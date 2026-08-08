#pragma once

#include <string>

#include "Component.h"

class Metadata : public Component {
public:
  static const Component::Type TYPE = Component::Type::METADATA;
  virtual Type getType() const override;

  Metadata() = default;
  Metadata(const std::string &name, bool isVisible = true) : name(name), isVisible(isVisible) {}

  std::string getName() const;
  void setName(std::string n);

  bool getIsVisible() const;
  void setIsVisible(bool v);

private:
  std::string name;
  bool isVisible = true;
};
