#include <iostream>

#include "geometry/Rectangle.h"

void Rectangle::draw() {
  if (renderer == nullptr) {
    return;
  }

  std::cout << "Drawing a rectangle..." << std::endl;

  int w = renderer->getWidth();
  int h = renderer->getHeight();
  float a = renderer->getAspectRatio();
  std::cout << "Image dimensions: " << w << " " << h << std::endl;

  int rw = width * h;
  int rh = height * h;
  std::cout << "Rectangle dimensions: " << rw << " " << rh << std::endl;

  int ci = (center.x / a + 0.5) * w;
  int cj = (-center.y + 0.5) * h;
  std::cout << "Center coords: " << ci << " " << cj << std::endl;

  for (int j = cj - rh / 2; j <= cj + rh / 2; j++) {
    for (int i = ci - rw / 2; i <= ci + rw / 2; i++) {
      if (j >= 0 && j < h && i >= 0 && i < w) {
        u32 r = color.x * 255.999;
        u32 g = color.y * 255.999;
        u32 b = color.z * 255.999;
        u32 a = color.w * 255.999;

        renderer->pixels[j * w + i] = r | (g << 8) | (b << 16) | (a << 24);
      }
    }
  }
}
