#include <iostream>

#include "geometry/Circle.h"

void Circle::draw() {
  if (renderer == nullptr) {
    return;
  }

  std::cout << "Drawing a circle..." << std::endl;

  int w = renderer->getWidth();
  int h = renderer->getHeight();
  float a = renderer->getAspectRatio();
  std::cout << "Image dimensions: " << w << " " << h << std::endl;

  int r = radius * h;
  std::cout << "Circle radius: " << r << std::endl;

  int ci = (center.x / a + 0.5) * w;
  int cj = (-center.y + 0.5) * h;
  std::cout << "Center coords: " << ci << " " << cj << std::endl;

  for (int j = cj - r; j <= cj + r; j++) {
    for (int i = ci - r; i <= ci + r; i++) {
      if (j >= 0 && j < h && i >= 0 && i < w && (j - cj) * (j - cj) + (i - ci) * (i - ci) <= r * r) {
        u32 r = color.x * 255.999;
        u32 g = color.y * 255.999;
        u32 b = color.z * 255.999;
        u32 a = color.w * 255.999;

        renderer->pixels[j * w + i] = r | (g << 8) | (b << 16) | (a << 24);
      }
    }
  }
}
