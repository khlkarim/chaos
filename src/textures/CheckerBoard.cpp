#include "textures/CheckerBoard.h"

Color CheckerBoard::getPrimary() const { return primary; }
void CheckerBoard::setPrimary(Color c) { primary = c; }

Color CheckerBoard::getSecondary() const { return secondary; }
void CheckerBoard::setSecondary(Color c) { secondary = c; }

float CheckerBoard::getUFreq() const { return uFreq; }
void CheckerBoard::setUFreq(float f) { uFreq = f; }

float CheckerBoard::getVFreq() const { return vFreq; }
void CheckerBoard::setVFreq(float f) { vFreq = f; }

Color CheckerBoard::at(Vec2 texCoords) const {
  Vec2 cellSize(1 / uFreq, 1 / vFreq);
  int i = texCoords.x / cellSize.x;
  int j = texCoords.y / cellSize.y;

  if (i % 2 == 0) {
    if (j % 2 == 0) {
      return primary;
    } else {
      return secondary;
    }
  } else {
    if (j % 2 == 0) {
      return secondary;
    } else {
      return primary;
    }
  }
}
