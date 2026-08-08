#define SHARED_IMPLEMENTATION
#include "shared.h"

constexpr const char *OUTPUT_FILE_PATH = "./crt/";
constexpr IO::FileFormat OUTPUT_FILE_FORMAT = IO::FileFormat::PNG;
constexpr IO::FileFormat INPUT_FILE_FORMAT = IO::FileFormat::CRT;

struct Collection {
  int count;
  std::string prefix, baseFilename;
};

int main() {
  std::vector<Collection> collections = {
      {
          .count = 5,
          .prefix = "./assets/hw07/",
          .baseFilename = "hw07-",
      },
      {
          .count = 4,
          .prefix = "./assets/hw08/",
          .baseFilename = "hw08-",
      },
      {
          .count = 5,
          .prefix = "./assets/hw09/",
          .baseFilename = "hw09-",
      },
      {
          .count = 9,
          .prefix = "./assets/hw11/",
          .baseFilename = "hw11-",
      },
      {
          .count = 2,
          .prefix = "./assets/hw12/",
          .baseFilename = "hw12-",
      },
  };

  for (auto &c : collections) {
    for (int i = 1; i < c.count; i++) {
      Scene scene;
      Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
      renderer.setSamplesPerPixel(RENDERER_SAMPLES_PER_PIXEL);
      renderer.setMaxDepth(RENDERER_MAX_DEPTH);

      auto idx = std::to_string(i);
      auto in = c.prefix + "scene" + idx + ".crtscene";
      auto out = OUTPUT_FILE_PATH + c.baseFilename + "scene" + idx + ".png";

      IO::load(scene, in, INPUT_FILE_FORMAT);
      renderer.render(scene);
      IO::save(renderer, out, OUTPUT_FILE_FORMAT);
    }
  }
}
