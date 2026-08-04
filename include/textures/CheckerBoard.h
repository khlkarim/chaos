#pragma once

#include "textures/Texture.h"

class CheckerBoard : public Texture {
public:
  CheckerBoard(Color primary = COLOR_WHITE, Color secondary = COLOR_BLACK, float uFreq = 10, float vFreq = 10)
      : primary(primary), secondary(secondary), uFreq(uFreq), vFreq(vFreq) {}

  Color getPrimary() const;
  void setPrimary(Color c);

  Color getSecondary() const;
  void setSecondary(Color c);

  float getUFreq() const;
  void setUFreq(float f);

  float getVFreq() const;
  void setVFreq(float f);

  Color at(Vec2 texCoords) const override;

private:
  float uFreq, vFreq;
  Color primary, secondary;
};
