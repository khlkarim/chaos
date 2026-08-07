#pragma once

#include "textures/Texture.h"

class Edge : public Texture {
public:
  Edge(Color e = COLOR_GREEN, Color i = COLOR_RED, float w = 0.05) : edgeColor(e), innerColor(i), edgeWidth(w) {}

  float getEdgeWidth() const;
  void setEdgeWidth(float f);

  Color getEdgeColor() const;
  void setEdgeColor(Color c);

  Color getInnerColor() const;
  void setInnerColor(Color c);

  Color at(Vec2 texCoords) const override;

private:
  float edgeWidth;
  Color edgeColor, innerColor;
};
