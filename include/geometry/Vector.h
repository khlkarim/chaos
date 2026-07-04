#pragma once

struct Vec2 {
  float x, y;

  float length();
  float length2();
  friend float dot(const Vec2 &v1, const Vec2 &v2);

  Vec2 &operator+=(const Vec2 &v);
  Vec2 &operator-=(const Vec2 &v);
  Vec2 &operator*=(const Vec2 &v);
  Vec2 &operator/=(const Vec2 &v);

  Vec2 &operator+=(const float &a);
  Vec2 &operator-=(const float &a);
  Vec2 &operator*=(const float &a);
  Vec2 &operator/=(const float &a);

  friend Vec2 operator+(const Vec2 &v1, const Vec2 &v2);
  friend Vec2 operator-(const Vec2 &v1, const Vec2 &v2);
  friend Vec2 operator*(const Vec2 &v1, const Vec2 &v2);
  friend Vec2 operator/(const Vec2 &v1, const Vec2 &v2);

  friend Vec2 operator+(const Vec2 &v, const float &a);
  friend Vec2 operator-(const Vec2 &v, const float &a);
  friend Vec2 operator*(const Vec2 &v, const float &a);
  friend Vec2 operator/(const Vec2 &v, const float &a);
};

struct Vec3 {
  float x, y, z;
};

struct Vec4 {
  float x, y, z, w;
};

using Color = Vec4;
