#pragma once

#include <string>

#include "renderer/Scene.h"
#include "components/Mesh.h"
#include "renderer/Renderer.h"

class IO {
public:
  enum FileFormat { PPM, PNG, JPEG, OBJ, CRT, JSON };

  static void save(const Renderer &renderer, const std::string &path, FileFormat format);
  static void load(Scene &scene, const std::string &path, FileFormat format);
  static void load(Mesh &mesh, const std::string &path, FileFormat format);
};
