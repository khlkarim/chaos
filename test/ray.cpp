#include "renderer/Renderer.h"

constexpr int IMAGE_WIDTH = 1280;
constexpr int IMAGE_HEIGHT = 720;
constexpr FileFormat OUTPUT_FILE_FORMAT = PNG;
constexpr const char *OUTPUT_FILE_PATH = "ray-output-01.png";

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);

  renderer.render(scene);
  renderer.write(OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}
