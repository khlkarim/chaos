#include <fstream>
#include <string>

#include "io/PPM.h"

void PPM::write(const char *filename, const int w, const int h, const int channels, const unsigned int *data) {
  if (filename == nullptr || data == nullptr) {
    return;
  }

  unsigned int maxVal = 255;
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
