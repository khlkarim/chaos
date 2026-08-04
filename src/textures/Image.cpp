#include "textures/Image.h"

int Image::getWidth() const { return width; }
void Image::setWidth(int w) { width = w; }

int Image::getHeight() const { return height; }
void Image::setHeight(int h) { height = h; }

int Image::getChannels() const { return channels; }
void Image::setChannels(int c) { channels = c == 3 || c == 4 ? c : channels; }

std::vector<float> &Image::getData() { return data; }
const std::vector<float> &Image::getData() const { return data; }
void Image::setData(const std::vector<float> &d) { data = d; }

Color Image::at(Vec2 texCoords) const {
  if (width == 0 || height == 0 || (channels != 3 && channels != 4) || data.empty()) {
    return COLOR_MAGENTA;
  }

  int i = width * texCoords.x;
  int j = height * texCoords.y;
  int idx = (j * width + i) * channels;

  if (channels == 3) {
    return Color(data[idx], data[idx + 1], data[idx + 2], 1);
  } else {
    return Color(data[idx], data[idx + 1], data[idx + 2], data[idx + 3]);
  }
}
