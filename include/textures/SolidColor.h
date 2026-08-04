#pragma once

#include "textures/Texture.h"

class SolidColor : public Texture {
public:
  SolidColor(Color albedo = COLOR_WHITE) : albedo(albedo) {}

  Color getAlbedo() const;
  void setAlbedo(Color c);

  Color at(Vec2 texCoords) const override;

private:
  Color albedo;
};
