#pragma once

#include <vector>

#include "renderer/Scene.h"

class Renderer {
public:
  std::vector<unsigned int> pixels;

  Renderer() = default;
  Renderer(int w, int h);

  int getWidth() const;
  int getHeight() const;
  float getAspectRatio() const;
  void setDimensions(int w, int h);

  float getViewportHeight() const;
  void setViewportHeight(float h);

  int getMaxDepth() const;
  void setMaxDepth(int depth);

  int getSamplesPerPixel() const;
  void setSamplesPerPixel(int spp);

  void render(Scene &scene);
  void setColor(int row, int col, Color color);

private:
  int width = 1280;
  float viewportHeight = 1;
  float aspectRatio = 1280. / 720.;

  int maxDepth = 10;
  int samplesPerPixel = 10;
};
