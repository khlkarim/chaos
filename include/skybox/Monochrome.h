#pragma once

#include "skybox/Skybox.h"

class Monochrome : public Skybox {
public:
  Monochrome(Color color = COLOR_BLUE) : color(color) {}

  Color getColor() const;
  void setColor(Color c);

  virtual Color getColor(const Ray &ray) const override;

private:
  Color color;
};
