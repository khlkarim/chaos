#define SHARED_IMPLEMENTATION
#include "shared.h"

constexpr const char *OUTPUT_FILE_PATH = "ray-output-01.png";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.setSamplesPerPixel(RENDERER_SAMPLES_PER_PIXEL);
  renderer.setMaxDepth(RENDERER_MAX_DEPTH);

  renderer.render(scene);
  IO::save(renderer, OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}
