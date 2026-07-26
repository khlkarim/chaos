#pragma once

class Component {
public:
  enum Type {
    METADATA,

    SDF,
    MESH,
    MATERIAL,
    TRANSFORM,

    TYPE_COUNT,
  };

  virtual ~Component() {}
  virtual Type getType() const = 0;
};
