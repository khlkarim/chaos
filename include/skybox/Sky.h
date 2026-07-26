#pragma once

#include "skybox/Skybox.h"

class Sky : public Skybox {
public:
  Sky(Color start = COLOR_WHITE, Color end = Color(0.5, 0.7, 1.0, 1.0)) : start(start), end(end) {}

  Color getStartColor() const;
  void setStartColor(Color c);

  Color getEndColor() const;
  void setEndColor(Color c);

  Color getColor(const Ray &ray) const override;

private:
  Color start, end;
};
