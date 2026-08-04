#pragma once

class Component {
public:
  enum Type {
    METADATA,

    HIERARCHY,
    TRANSFORM,
    GEOMETRY,
    MATERIAL,

    TYPE_COUNT,
  };

  virtual ~Component() {}
  virtual Type getType() const = 0;
};
