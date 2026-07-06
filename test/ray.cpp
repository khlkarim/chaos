#include "renderer/Renderer.h"

#define IMAGE_WIDTH 1280
#define IMAGE_HEIGHT 720
#define OUTPUT_FILE_PATH "ray-output-00.png"
#define OUTPUT_FILE_FORMAT PNG

int main() {
  Scene scene;
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);

  renderer.render(scene);
  renderer.write(OUTPUT_FILE_PATH, OUTPUT_FILE_FORMAT);
}
