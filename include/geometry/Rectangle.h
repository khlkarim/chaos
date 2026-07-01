#pragma once

#include "Shape.h"
#include "Vector.h"

class Rectangle : public Shape {
public:
  float width;
  float height;
  Vec2 center;
  Color color;

  void draw() override;
};
