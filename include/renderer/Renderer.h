#pragma once

#include <string>
#include <vector>

using u32 = unsigned int;
enum FileFormat { PPM, PNG, JPEG };

class Renderer {
public:
  std::vector<u32> pixels;

  Renderer(const int w, const int h);

  int getWidth() const;
  int getHeight() const;
  float getAspectRatio() const;
  void render(const std::string path, const FileFormat format) const;

private:
  int width;
  float aspectRatio;
};
