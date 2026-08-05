#define SHARED_IMPLEMENTATION
#include "shared.h"

constexpr const char *OUTPUT_FILE_PATH = "./crt-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;
constexpr const char *INPUT_FILE_PATH = "./assets/models/scene0.crtscene";
constexpr IO::FileFormat INPUT_FILE_FORMAT = IO::FileFormat::CRT;

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(RENDERER_SAMPLES_PER_PIXEL);
  renderer.setMaxDepth(RENDERER_MAX_DEPTH);

  IO::load(scene, INPUT_FILE_PATH, INPUT_FILE_FORMAT);
  renderer.render(scene);
  IO::save(renderer, OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}
