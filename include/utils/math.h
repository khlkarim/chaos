#pragma once

constexpr float EPSILON = 1e-6;
constexpr float PI = 3.14159265359;

float getRandomFLoat();
int getRandomInt(int min, int max);
float toRadians(float degrees);
float toDegrees(float radians);
float gammaToLinear(float a);
float linearToGamma(float a);
