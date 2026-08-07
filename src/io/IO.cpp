#include <string>
#include <vector>
#include <iostream>

#include "utils/stb_image.h"
#include "utils/stb_image_write.h"

#include "io/CRT.h"
#include "io/OBJ.h"
#include "io/PPM.h"
#include "io/IO.h"

void IO::save(const Renderer &renderer, const std::string &path, FileFormat format) {
  std::cout << "Saving rendered image to: " << path << std::endl;

  int channels = 4;
  int w = renderer.getWidth();
  int h = renderer.getHeight();
  float a = renderer.getAspectRatio();
  std::cout << "Image dimensions: " << w << " " << h << std::endl;

  switch (format) {
  case PPM:
    PPM::write(path.c_str(), w, h, channels, renderer.pixels.data());
    break;
  case PNG:
    stbi_write_png(path.c_str(), w, h, channels, renderer.pixels.data(), w * channels);
    break;
  case JPEG:
    stbi_write_jpg(path.c_str(), w, h, channels, renderer.pixels.data(), 100);
    break;
  default:
    std::cout << "Unsupported format." << std::endl;
  }
}

void IO::load(Renderer &renderer, const std::string &path, FileFormat format) {
  std::cout << "Loading renderer from: " << path << std::endl;

  switch (format) {
  case CRT:
    CRT::load(renderer, path);
    break;
  default:
    std::cout << "Unsupported format." << std::endl;
  }
}

void IO::load(Scene &scene, const std::string &path, FileFormat format) {
  std::cout << "Loading scene from: " << path << std::endl;

  switch (format) {
  case CRT:
    CRT::load(scene, path);
    break;
  default:
    std::cout << "Unsupported format." << std::endl;
  }
}

std::shared_ptr<Mesh> IO::loadMesh(const std::string &path, FileFormat format) {
  std::cout << "Loading mesh from: " << path << std::endl;

  switch (format) {
  case OBJ:
    return OBJ::loadMesh(path);
    break;
  case CRT:
    return CRT::loadMesh(path);
    break;
  default:
    std::cout << "Unsupported format." << std::endl;
    return nullptr;
  }
}

std::shared_ptr<Image> IO::loadImage(const std::string &path, FileFormat format) {
  std::cout << "Loading image from: " << path << std::endl;

  int w = 0, h = 0, c = 0;
  float *d = stbi_loadf(path.c_str(), &w, &h, &c, 0);

  int size = w * h * c;
  return std::make_shared<Image>(w, h, c, std::vector<float>(d, d + size));
}
