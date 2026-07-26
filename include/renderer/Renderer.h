#pragma once

#include <vector>

#include "renderer/Scene.h"

class Renderer {
public:
  std::vector<unsigned int> pixels;

  Renderer() = default;
  Renderer(const int w, const int h);

  int getWidth() const;
  int getHeight() const;
  float getAspectRatio() const;

  int getMaxDepth() const;
  void setMaxDepth(int depth);

  int getSamplesPerPixel() const;
  void setSamplesPerPixel(int spp);

  void render(Scene &scene);
  void setColor(const int &row, const int &col, const Color &color);

private:
  int width = 1280;
  float aspectRatio = 1280. / 720.;

  int maxDepth = 10;
  int samplesPerPixel = 10;
};
