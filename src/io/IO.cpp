#include <string>
#include <vector>
#include <iostream>

#include "utils/stb_image_write.h"

#include "io/CRT.h"
#include "io/IO.h"
#include "io/OBJ.h"
#include "io/PPM.h"

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

void IO::load(Mesh &mesh, const std::string &path, FileFormat format) {
  std::cout << "Loading mesh from: " << path << std::endl;

  switch (format) {
  case OBJ:
    OBJ::load(mesh, path);
    break;
  default:
    std::cout << "Unsupported format." << std::endl;
  }
}
