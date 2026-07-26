#include "skybox/Monochrome.h"

Color Monochrome::getColor() const { return color; }
void Monochrome::setColor(Color c) { color = c; }

Color Monochrome::getColor(const Ray &ray) const { return color; }
