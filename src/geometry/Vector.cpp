#include <cmath>

#include "geometry/Vector.h"

float Vec2::length() { return std::sqrt(length2()); }
float Vec2::length2() { return x * x + y * y; }
float dot(const Vec2 &v1, const Vec2 &v2) { return v1.x * v2.x + v1.y * v1.y; }

Vec2 &Vec2::operator+=(const Vec2 &v) {
  this->x += v.x;
  this->y += v.y;
  return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &v) {
  this->x -= v.x;
  this->y -= v.y;
  return *this;
}

Vec2 &Vec2::operator*=(const Vec2 &v) {
  this->x *= v.x;
  this->y *= v.y;
  return *this;
}

Vec2 &Vec2::operator/=(const Vec2 &v) {
  this->x /= v.x;
  this->y /= v.y;
  return *this;
}

Vec2 &Vec2::operator+=(const float &a) {
  this->x += a;
  this->y += a;
  return *this;
}

Vec2 &Vec2::operator-=(const float &a) {
  this->x -= a;
  this->y -= a;
  return *this;
}

Vec2 &Vec2::operator*=(const float &a) {
  this->x *= a;
  this->y *= a;
  return *this;
}

Vec2 &Vec2::operator/=(const float &a) {
  this->x /= a;
  this->y /= a;
  return *this;
}

Vec2 operator+(const Vec2 &v1, const Vec2 &v2) {
  return {
      .x = v1.x + v2.x,
      .y = v1.y + v2.y,
  };
}

Vec2 operator-(const Vec2 &v1, const Vec2 &v2) {
  return {
      .x = v1.x - v2.x,
      .y = v1.y - v2.y,
  };
}

Vec2 operator*(const Vec2 &v1, const Vec2 &v2) {
  return {
      .x = v1.x * v2.x,
      .y = v1.y * v2.y,
  };
}

Vec2 operator/(const Vec2 &v1, const Vec2 &v2) {
  return {
      .x = v1.x / v2.x,
      .y = v1.y / v2.y,
  };
}

Vec2 operator+(const Vec2 &v, const float &a) {
  return {
      .x = v.x + a,
      .y = v.y + a,
  };
}

Vec2 operator-(const Vec2 &v, const float &a) {
  return {
      .x = v.x - a,
      .y = v.y - a,
  };
}

Vec2 operator*(const Vec2 &v, const float &a) {
  return {
      .x = v.x * a,
      .y = v.y * a,
  };
}

Vec2 operator/(const Vec2 &v, const float &a) {
  return {
      .x = v.x / a,
      .y = v.y / a,
  };
}
