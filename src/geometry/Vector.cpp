#include <cmath>

#include "geometry/Vector.h"

float Vec2::length() const { return std::sqrt(length2()); }
float Vec2::length2() const { return x * x + y * y; }
float dot(const Vec2 &v1, const Vec2 &v2) { return v1.x * v2.x + v1.y * v2.y; }

Vec2 normalize(const Vec2 &v) {
  Vec2 u = v / v.length();
  return u;
}

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
      v1.x + v2.x,
      v1.y + v2.y,
  };
}

Vec2 operator-(const Vec2 &v1, const Vec2 &v2) {
  return {
      v1.x - v2.x,
      v1.y - v2.y,
  };
}

Vec2 operator*(const Vec2 &v1, const Vec2 &v2) {
  return {
      v1.x * v2.x,
      v1.y * v2.y,
  };
}

Vec2 operator/(const Vec2 &v1, const Vec2 &v2) {
  return {
      v1.x / v2.x,
      v1.y / v2.y,
  };
}

Vec2 operator+(const Vec2 &v, const float &a) {
  return {
      v.x + a,
      v.y + a,
  };
}

Vec2 operator-(const Vec2 &v, const float &a) {
  return {
      v.x - a,
      v.y - a,
  };
}

Vec2 operator*(const Vec2 &v, const float &a) {
  return {
      v.x * a,
      v.y * a,
  };
}

Vec2 operator/(const Vec2 &v, const float &a) {
  return {
      v.x / a,
      v.y / a,
  };
}

float Vec3::length() const { return std::sqrt(length2()); }
float Vec3::length2() const { return x * x + y * y + z * z; }
float dot(const Vec3 &v1, const Vec3 &v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
  return {
      v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x,
  };
}

Vec3 normalize(const Vec3 &v) {
  Vec3 u = v / v.length();
  return u;
}

Vec3 &Vec3::operator+=(const Vec3 &v) {
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
  return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &v) {
  this->x -= v.x;
  this->y -= v.y;
  this->z -= v.z;
  return *this;
}

Vec3 &Vec3::operator*=(const Vec3 &v) {
  this->x *= v.x;
  this->y *= v.y;
  this->z *= v.z;
  return *this;
}

Vec3 &Vec3::operator/=(const Vec3 &v) {
  this->x /= v.x;
  this->y /= v.y;
  this->z /= v.z;
  return *this;
}

Vec3 &Vec3::operator+=(const float &a) {
  this->x += a;
  this->y += a;
  this->z += a;
  return *this;
}

Vec3 &Vec3::operator-=(const float &a) {
  this->x -= a;
  this->y -= a;
  this->z -= a;
  return *this;
}

Vec3 &Vec3::operator*=(const float &a) {
  this->x *= a;
  this->y *= a;
  this->z *= a;
  return *this;
}

Vec3 &Vec3::operator/=(const float &a) {
  this->x /= a;
  this->y /= a;
  this->z /= a;
  return *this;
}

Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
  return {
      v1.x + v2.x,
      v1.y + v2.y,
      v1.z + v2.z,
  };
}

Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
  return {
      v1.x - v2.x,
      v1.y - v2.y,
      v1.z - v2.z,
  };
}

Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
  return {
      v1.x * v2.x,
      v1.y * v2.y,
      v1.z * v2.z,
  };
}

Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
  return {
      v1.x / v2.x,
      v1.y / v2.y,
      v1.z / v2.z,
  };
}

Vec3 operator+(const Vec3 &v, const float &a) {
  return {
      v.x + a,
      v.y + a,
      v.z + a,
  };
}

Vec3 operator-(const Vec3 &v, const float &a) {
  return {
      v.x - a,
      v.y - a,
      v.z - a,
  };
}

Vec3 operator*(const Vec3 &v, const float &a) {
  return {
      v.x * a,
      v.y * a,
      v.z * a,
  };
}

Vec3 operator/(const Vec3 &v, const float &a) {
  return {
      v.x / a,
      v.y / a,
      v.z / a,
  };
}

float Vec4::length() const { return std::sqrt(length2()); }
float Vec4::length2() const { return x * x + y * y + z * z + w * w; }
float dot(const Vec4 &v1, const Vec4 &v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }

Vec4 normalize(const Vec4 &v) {
  Vec4 u = v / v.length();
  return u;
}

Vec4 &Vec4::operator+=(const Vec4 &v) {
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
  this->w += v.w;
  return *this;
}

Vec4 &Vec4::operator-=(const Vec4 &v) {
  this->x -= v.x;
  this->y -= v.y;
  this->z -= v.z;
  this->w -= v.w;
  return *this;
}

Vec4 &Vec4::operator*=(const Vec4 &v) {
  this->x *= v.x;
  this->y *= v.y;
  this->z *= v.z;
  this->w *= v.w;
  return *this;
}

Vec4 &Vec4::operator/=(const Vec4 &v) {
  this->x /= v.x;
  this->y /= v.y;
  this->z /= v.z;
  this->w /= v.w;
  return *this;
}

Vec4 &Vec4::operator+=(const float &a) {
  this->x += a;
  this->y += a;
  this->z += a;
  this->w += a;
  return *this;
}

Vec4 &Vec4::operator-=(const float &a) {
  this->x -= a;
  this->y -= a;
  this->z -= a;
  this->w -= a;
  return *this;
}

Vec4 &Vec4::operator*=(const float &a) {
  this->x *= a;
  this->y *= a;
  this->z *= a;
  this->w *= a;
  return *this;
}

Vec4 &Vec4::operator/=(const float &a) {
  this->x /= a;
  this->y /= a;
  this->z /= a;
  this->w /= a;
  return *this;
}

Vec4 operator+(const Vec4 &v1, const Vec4 &v2) {
  return {
      v1.x + v2.x,
      v1.y + v2.y,
      v1.z + v2.z,
      v1.w + v2.w,
  };
}

Vec4 operator-(const Vec4 &v1, const Vec4 &v2) {
  return {
      v1.x - v2.x,
      v1.y - v2.y,
      v1.z - v2.z,
      v1.w - v2.w,
  };
}

Vec4 operator*(const Vec4 &v1, const Vec4 &v2) {
  return {
      v1.x * v2.x,
      v1.y * v2.y,
      v1.z * v2.z,
      v1.w * v2.w,
  };
}

Vec4 operator/(const Vec4 &v1, const Vec4 &v2) {
  return {
      v1.x / v2.x,
      v1.y / v2.y,
      v1.z / v2.z,
      v1.w / v2.w,
  };
}

Vec4 operator+(const Vec4 &v, const float &a) {
  return {
      v.x + a,
      v.y + a,
      v.z + a,
      v.w + a,
  };
}

Vec4 operator-(const Vec4 &v, const float &a) {
  return {
      v.x - a,
      v.y - a,
      v.z - a,
      v.w - a,
  };
}

Vec4 operator*(const Vec4 &v, const float &a) {
  return {
      v.x * a,
      v.y * a,
      v.z * a,
      v.w * a,
  };
}

Vec4 operator/(const Vec4 &v, const float &a) {
  return {
      v.x / a,
      v.y / a,
      v.z / a,
      v.w / a,
  };
}
