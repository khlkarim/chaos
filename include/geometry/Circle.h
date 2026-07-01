#pragma once

#include "Shape.h"
#include "Vector.h"

class Circle : public Shape {
public:
  Vec2 center;
  float radius;
  Color color;

  void draw() override;
};
