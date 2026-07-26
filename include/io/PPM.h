#pragma once

class PPM {
public:
  static void write(const char *filename, const int w, const int h, const int channels, const unsigned int *data);
};
