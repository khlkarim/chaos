#include "textures/Edge.h"

Color Edge::getEdgeColor() const { return edgeColor; }
void Edge::setEdgeColor(Color c) { edgeColor = c; }

Color Edge::getInnerColor() const { return innerColor; }
void Edge::setInnerColor(Color c) { innerColor = c; }

float Edge::getEdgeWidth() const { return edgeWidth; }
void Edge::setEdgeWidth(float f) { edgeWidth = f; }

Color Edge::at(Vec2 texCoords) const {
  float u = texCoords.x, v = texCoords.y, w = 1 - u - v;

  if (u < edgeWidth || v < edgeWidth || w < edgeWidth) {
    return edgeColor;
  } else {
    return innerColor;
  }
}
