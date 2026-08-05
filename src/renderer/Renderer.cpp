#include <cmath>
#include <iostream>

#include "utils/math.h"
#include "renderer/Renderer.h"

Renderer::Renderer(int w, int h) {
  width = w;
  aspectRatio = (float)w / h;
  pixels = std::vector<unsigned int>(h * w, 0xffu << 24);
}

void Renderer::setDimensions(int w, int h) {
  width = w;
  aspectRatio = (float)w / h;
  pixels.resize(h * w, 0xffu << 24);
}

int Renderer::getWidth() const { return width; }
float Renderer::getAspectRatio() const { return aspectRatio; }
int Renderer::getHeight() const { return std::max(1, static_cast<int>(width / aspectRatio)); }

int Renderer::getMaxDepth() const { return maxDepth; }
void Renderer::setMaxDepth(int depth) { maxDepth = depth; }

int Renderer::getSamplesPerPixel() const { return samplesPerPixel; }
void Renderer::setSamplesPerPixel(int spp) { samplesPerPixel = spp; }

void Renderer::render(Scene &scene) {
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
        Ray ray(origin, direction);

        scene.setColor(ray, maxDepth);
        color += ray.getColor();
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

void Renderer::setColor(int row, int col, Color color) {
  int height = getHeight();
  if (row < 0 || row >= height || col < 0 || col >= width) {
    return;
  }

  unsigned int r = linearToGamma(clamp(color.x, 0, 1)) * 255.999;
  unsigned int g = linearToGamma(clamp(color.y, 0, 1)) * 255.999;
  unsigned int b = linearToGamma(clamp(color.z, 0, 1)) * 255.999;
  unsigned int a = clamp(color.w, 0, 1) * 255.999;

  pixels[row * width + col] = r | (g << 8) | (b << 16) | (a << 24);
}
