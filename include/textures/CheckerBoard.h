#pragma once

#include "textures/Texture.h"

class CheckerBoard : public Texture {
public:
  CheckerBoard(Color p = COLOR_WHITE, Color s = COLOR_BLACK, float uf = 10, float vf = 10)
      : primary(p), secondary(s), uFreq(uf), vFreq(vf) {}

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
