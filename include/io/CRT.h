#pragma once

#include "renderer/Scene.h"
#include "components/Mesh.h"
#include "renderer/Renderer.h"

class CRT {
public:
  static void load(Mesh &mesh, const std::string &path);
  static void load(Scene &scene, const std::string &path);
  static void load(Renderer &renderer, const std::string &path);

private:
  struct Schema {
    struct {
      std::vector<float> background_color;
      std::vector<int> image_settings;
    } settings;

    struct {
      std::vector<float> matrix;
      std::vector<float> position;
    } camera;

    std::vector<Mesh> objects;
  };

  static Schema parse(const std::string &path);
};
