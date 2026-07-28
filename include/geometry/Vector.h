#pragma once

#include <ostream>

struct Vec2 {
  float x = 0, y = 0;

  constexpr Vec2() = default;
  constexpr Vec2(float a) : x(a), y(a) {}
  constexpr Vec2(float x, float y) : x(x), y(y) {}

  static Vec2 getRandomUnitSquare();
  static Vec2 getRandomUnitCircle();

  float length() const;
  float length2() const;
  friend Vec2 normalize(const Vec2 &v);
  friend float dot(const Vec2 &v1, const Vec2 &v2);

  Vec2 operator+() const;
  Vec2 operator-() const;

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

  friend std::ostream &operator<<(std::ostream &os, const Vec2 &v);
};

struct Vec3 {
  float x = 0, y = 0, z = 0;

  constexpr Vec3() = default;
  constexpr Vec3(float a) : x(a), y(a), z(a) {}
  constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  static Vec3 getRandomUnitCube();
  static Vec3 getRandomUnitSphere();

  float length() const;
  float length2() const;
  Vec3 reflect(const Vec3 &n) const;
  Vec3 refract(const Vec3 &n, float ri) const;

  friend Vec3 normalize(const Vec3 &v);
  friend float dot(const Vec3 &v1, const Vec3 &v2);
  friend Vec3 cross(const Vec3 &v1, const Vec3 &v2);

  Vec3 operator+() const;
  Vec3 operator-() const;

  Vec3 &operator+=(const Vec3 &v);
  Vec3 &operator-=(const Vec3 &v);
  Vec3 &operator*=(const Vec3 &v);
  Vec3 &operator/=(const Vec3 &v);

  Vec3 &operator+=(const float &a);
  Vec3 &operator-=(const float &a);
  Vec3 &operator*=(const float &a);
  Vec3 &operator/=(const float &a);

  friend Vec3 operator+(const Vec3 &v1, const Vec3 &v2);
  friend Vec3 operator-(const Vec3 &v1, const Vec3 &v2);
  friend Vec3 operator*(const Vec3 &v1, const Vec3 &v2);
  friend Vec3 operator/(const Vec3 &v1, const Vec3 &v2);

  friend Vec3 operator+(const Vec3 &v, const float &a);
  friend Vec3 operator-(const Vec3 &v, const float &a);
  friend Vec3 operator*(const Vec3 &v, const float &a);
  friend Vec3 operator/(const Vec3 &v, const float &a);

  friend std::ostream &operator<<(std::ostream &os, const Vec3 &v);
};

struct Vec4 {
  float x = 0, y = 0, z = 0, w = 0;

  constexpr Vec4() = default;
  constexpr Vec4(float a) : x(a), y(a), z(a), w(a) {}
  constexpr Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  static Vec4 getRandom();

  float length() const;
  float length2() const;
  friend Vec4 normalize(const Vec4 &v);
  friend float dot(const Vec4 &v1, const Vec4 &v2);

  Vec4 operator+() const;
  Vec4 operator-() const;

  Vec4 &operator+=(const Vec4 &v);
  Vec4 &operator-=(const Vec4 &v);
  Vec4 &operator*=(const Vec4 &v);
  Vec4 &operator/=(const Vec4 &v);

  Vec4 &operator+=(const float &a);
  Vec4 &operator-=(const float &a);
  Vec4 &operator*=(const float &a);
  Vec4 &operator/=(const float &a);

  friend Vec4 operator+(const Vec4 &v1, const Vec4 &v2);
  friend Vec4 operator-(const Vec4 &v1, const Vec4 &v2);
  friend Vec4 operator*(const Vec4 &v1, const Vec4 &v2);
  friend Vec4 operator/(const Vec4 &v1, const Vec4 &v2);

  friend Vec4 operator+(const Vec4 &v, const float &a);
  friend Vec4 operator-(const Vec4 &v, const float &a);
  friend Vec4 operator*(const Vec4 &v, const float &a);
  friend Vec4 operator/(const Vec4 &v, const float &a);

  friend std::ostream &operator<<(std::ostream &os, const Vec4 &v);
};

using Color = Vec4;
constexpr Color COLOR_BLACK = Color(0, 0, 0, 1);
constexpr Color COLOR_GREY = Color(0.5, 0.5, 0.5, 1);
constexpr Color COLOR_WHITE = Color(1, 1, 1, 1);
constexpr Color COLOR_RED = Color(1, 0, 0, 1);
constexpr Color COLOR_GREEN = Color(0, 1, 0, 1);
constexpr Color COLOR_BLUE = Color(0, 0, 1, 1);
