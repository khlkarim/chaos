#pragma once

#include <vector>

#include "textures/Texture.h"

class Image : public Texture {
public:
  Image() = default;
  Image(int w, int h, int c, const std::vector<float> &d) : width(w), height(h), channels(c), data(d) {}

  int getWidth() const;
  void setWidth(int w);

  int getHeight() const;
  void setHeight(int h);

  int getChannels() const;
  void setChannels(int c);

  std::vector<float> &getData();
  const std::vector<float> &getData() const;
  void setData(const std::vector<float> &data);

  virtual Color at(Vec2 texCoords) const override;

private:
  std::vector<float> data;
  int width = 0, height = 0, channels = 0;
};
