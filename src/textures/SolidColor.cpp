#include "textures/SolidColor.h"

Color SolidColor::getAlbedo() const { return albedo; }
void SolidColor::setAlbedo(Color c) { albedo = c; }

Color SolidColor::at(Vec2 texCoords) const { return albedo; }
