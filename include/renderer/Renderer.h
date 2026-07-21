#pragma once

#include <string>
#include <vector>

#include "renderer/Scene.h"

using u32 = unsigned int;
enum FileFormat { PPM, PNG, JPEG };

class Renderer {
public:
  std::vector<u32> pixels;

  Renderer() = default;
  Renderer(const int w, const int h);

  int getWidth() const;
  int getHeight() const;
  float getAspectRatio() const;

  int getMaxDepth() const;
  void setMaxDepth(int depth);

  int getSamplesPerPixel() const;
  void setSamplesPerPixel(int spp);

  void render(const Scene &scene);
  void setColor(const int &row, const int &col, const Color &color);

  void write(const std::string &path, const FileFormat &format) const;

private:
  int width = 1280;
  float aspectRatio = 1280. / 720.;

  int maxDepth = 10;
  int samplesPerPixel = 10;
};
