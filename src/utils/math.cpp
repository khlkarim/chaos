#include <cstdlib>

#include "utils/math.h"

float getRandomFLoat() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }
float toRadians(float degrees) { return degrees * PI / 180.f; }
float toDegrees(float radians) { return radians * 180.f / PI; }
