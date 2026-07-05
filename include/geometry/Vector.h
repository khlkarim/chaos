#pragma once

struct Vec2 {
  float x = 0, y = 0;

  Vec2() = default;
  Vec2(float a) : x(a), y(a) {}
  Vec2(float x, float y) : x(x), y(y) {}

  float length() const;
  float length2() const;
  friend Vec2 normalize(const Vec2 &v);
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
  float x = 0, y = 0, z = 0;

  Vec3() = default;
  Vec3(float a) : x(a), y(a), z(a) {}
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  float length() const;
  float length2() const;
  friend Vec3 normalize(const Vec3 &v);
  friend float dot(const Vec3 &v1, const Vec3 &v2);
  friend Vec3 cross(const Vec3 &v1, const Vec3 &v2);

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
};

struct Vec4 {
  float x = 0, y = 0, z = 0, w = 0;

  Vec4() = default;
  Vec4(float a) : x(a), y(a), z(a), w(a) {}
  Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  float length() const;
  float length2() const;
  friend Vec4 normalize(const Vec4 &v);
  friend float dot(const Vec4 &v1, const Vec4 &v2);

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
};

using Color = Vec4;
