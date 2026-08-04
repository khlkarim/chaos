#include <cmath>

#include "utils/math.h"

int getRandomInt(int min, int max) { return min + (max - min) * getRandomFLoat(); }
float getRandomFLoat() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }

float toRadians(float degrees) { return degrees * PI / 180.f; }
float toDegrees(float radians) { return radians * 180.f / PI; }

float gammaToLinear(float a) { return a * a; }
float linearToGamma(float a) { return a > 0 ? std::sqrt(a) : 0; }

float clamp(float x, float min, float max) { return x < min ? min : x > max ? max : x; }
