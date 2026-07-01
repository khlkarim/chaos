#pragma once

#include <memory>

#include "renderer/Renderer.h"

class Shape {
public:
  virtual void draw() = 0;
  std::shared_ptr<Renderer> getRenderer() const { return renderer; }
  void setRenderer(std::shared_ptr<Renderer> r) { renderer = r; }

protected:
  std::shared_ptr<Renderer> renderer;
};
