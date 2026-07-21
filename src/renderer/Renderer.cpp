#include <cmath>
#include <fstream>
#include <iostream>

#include "renderer/Renderer.h"
#include "utils/math.h"
#include "utils/stb_image_write.h"

void write_ppm(const char *filename, const int w, const int h, const int channels, const u32 *data);

Renderer::Renderer(const int w, const int h) {
  width = w;
  aspectRatio = (float)w / h;
  pixels = std::vector<u32>(h * w, 0xffu << 24);
}

int Renderer::getHeight() const {
  int height = width / aspectRatio;
  return std::max(1, height);
}

int Renderer::getWidth() const { return width; }
float Renderer::getAspectRatio() const { return aspectRatio; }

int Renderer::getMaxDepth() const { return maxDepth; }
void Renderer::setMaxDepth(int depth) { maxDepth = depth; }

int Renderer::getSamplesPerPixel() const { return samplesPerPixel; }
void Renderer::setSamplesPerPixel(int spp) { samplesPerPixel = spp; }

void Renderer::render(const Scene &scene) {
  int w = getWidth();
  int h = getHeight();
  float a = getAspectRatio();
  const Camera &camera = scene.getCamera();

  std::cout << "Image Width: " << w << std::endl;
  std::cout << "Image Height: " << h << std::endl;
  std::cout << std::endl;

  Vec3 up = camera.getUp();
  Vec3 front = camera.getFront();
  Vec3 right = camera.getRight();
  Vec3 pos = camera.getPosition();

  std::cout << "Camera Up: " << up << std::endl;
  std::cout << "Camera Right: " << right << std::endl;
  std::cout << "Camera Front: " << front << std::endl;
  std::cout << "Camera Position: " << pos << std::endl;
  std::cout << std::endl;

  float fov = camera.getFov();
  float np = camera.getNearPlane();
  float viewportHeight = 2.0 * std::tan(toRadians(fov)) * np;
  float viewportWidth = a * viewportHeight;

  std::cout << "Viewport Width: " << viewportWidth << std::endl;
  std::cout << "Viewport Height: " << viewportHeight << std::endl;
  std::cout << std::endl;

  Vec3 u = viewportWidth * right;
  Vec3 v = -viewportHeight * up;
  Vec3 dU = u / w;
  Vec3 dV = v / h;
  Vec3 pixel00 = pos + np * front - 0.5 * (u + v) + 0.5 * (dU + dV);

  std::cout << "Pixels[0, 0]: " << pixel00 << std::endl;
  std::cout << std::endl;

  int workloadProgress = 0;
  float workloadProgressPercentage = 0;
  int totalWorkload = h * w;

  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      Color color;

      for (int k = 0; k < samplesPerPixel; k++) {
        Vec2 rand = Vec2::getRandomUnitSquare();

        Vec3 origin = pixel00 + (i + rand.x) * dU + (j + rand.y) * dV;
        Vec3 direction = normalize(origin - pos);
        Ray r(origin, direction);

        color += scene.getColor(r, maxDepth);
      }

      color /= samplesPerPixel;
      setColor(j, i, color);

      workloadProgress++;
      float a = (float)workloadProgress / totalWorkload;
      float p = ((int)(a * 10)) / 10.;

      if (p > workloadProgressPercentage) {
        workloadProgressPercentage = p;
        std::cout << "Progress: " << workloadProgressPercentage * 100 << "%" << std::endl;
      }
    }
  }

  std::cout << std::endl;
}

void Renderer::write(const std::string &path, const FileFormat &format) const {
  std::cout << "Exporting image..." << std::endl;

  int channels = 4;
  int w = getWidth();
  int h = getHeight();
  float a = getAspectRatio();
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

  f.close();
}
