#include <fstream>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "utils/stb_image_write.h"

#include "renderer/Renderer.h"

void write_ppm(const char *filename, const int w, const int h, const int channels, const u32 *data);

Renderer::Renderer(const int w, const int h) {
  width = w;
  aspectRatio = (float)w / h;
  pixels = std::vector<u32>(h * w, 0xffu << 24);
}

int Renderer::getWidth() const { return width; }
int Renderer::getHeight() const { return width / aspectRatio; }
float Renderer::getAspectRatio() const { return aspectRatio; }

void Renderer::setColor(const int &row, const int &col, const Color &color) {
  int height = getHeight();
  if (row < 0 || row >= height || col < 0 || col >= width) {
    return;
  }

  u32 r = color.x * 255.999;
  u32 g = color.y * 255.999;
  u32 b = color.z * 255.999;
  u32 a = color.w * 255.999;
  pixels[row * width + col] = r | (g << 8) | (b << 16) | (a << 24);
}

void Renderer::render(const std::string path, const FileFormat format) const {
  std::cout << "Exporting image..." << std::endl;

  int channels = 4;
  int w = getWidth();
  int h = getHeight();
  std::cout << "Image dimensions: " << w << " " << h << std::endl;

  switch (format) {
  case PPM:
    write_ppm(path.c_str(), w, h, channels, pixels.data());
    break;
  case PNG:
    stbi_write_png(path.c_str(), w, h, channels, pixels.data(), w * channels);
    break;
  case JPEG:
    stbi_write_jpg(path.c_str(), w, h, channels, pixels.data(), 100);
    break;
  default:
    std::cout << "Unsupported image format." << std::endl;
  }
}

void write_ppm(const char *filename, const int w, const int h, const int channels, const u32 *data) {
  if (filename == nullptr || data == nullptr) {
    return;
  }

  u32 maxVal = 255;
  std::string magicNumber = "P3";

  std::ofstream f(filename);
  f << magicNumber << std::endl;
  f << w << " " << h << std::endl;
  f << maxVal << std::endl;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      f << ((data[i * w + j] >> (8 * 3)) & 0xff) << " ";
      f << ((data[i * w + j] >> (8 * 2)) & 0xff) << " ";
      f << ((data[i * w + j] >> 8) & 0xff) << " ";
    }
    f << std::endl;
  }
}
