#include "io/IO.h"

constexpr int IMAGE_WIDTH = 320;
constexpr int IMAGE_HEIGHT = 180;
constexpr const char *OUTPUT_FILE_PATH = "./crt-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;
constexpr const char *INPUT_FILE_PATH = "./assets/scene0.crtscene";
constexpr IO::FileFormat INPUT_FILE_FORMAT = IO::FileFormat::CRT;

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(5);

  IO::load(scene, INPUT_FILE_PATH, INPUT_FILE_FORMAT);
  renderer.render(scene);
  IO::save(renderer, OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}
