#include <cmath>

#include "utils/math.h"
#include "geometry/Vector.h"

Vec2 Vec2::getRandomUnitSquare() { return {getRandomFLoat(), getRandomFLoat()}; }

Vec2 Vec2::getRandomUnitCircle() {
  float theta = 2 * PI * getRandomFLoat();
  return {std::cos(theta), std::sin(theta)};
}

float Vec2::length() const { return std::sqrt(length2()); }
float Vec2::length2() const { return x * x + y * y; }

Vec2 Vec2::rotate(float theta) const {
  float c = std::cos(theta);
  float s = std::sin(theta);
  return {c * x - s * y, s * x + c * y};
}

float dot(const Vec2 &v1, const Vec2 &v2) { return v1.x * v2.x + v1.y * v2.y; }

Vec2 normalize(const Vec2 &v) {
  Vec2 u = v / v.length();
  return u;
}

Vec2 Vec2::operator+() const { return {x, y}; }
Vec2 Vec2::operator-() const { return {-x, -y}; }

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

std::ostream &operator<<(std::ostream &os, const Vec2 &v) {
  os << "(" << v.x << ", " << v.y << ")";
  return os;
}

Vec3 Vec3::getRandomUnitCube() { return {getRandomFLoat(), getRandomFLoat(), getRandomFLoat()}; }

Vec3 Vec3::getRandomUnitSphere() {
  float phi = 2 * PI * getRandomFLoat();
  float theta = 2 * PI * getRandomFLoat();
  return {std::cos(theta) * std::cos(phi), std::sin(theta) * std::cos(phi), std::sin(phi)};
}

float Vec3::length() const { return std::sqrt(length2()); }
float Vec3::length2() const { return x * x + y * y + z * z; }

Vec3 Vec3::reflect(const Vec3 &n) const { return *this - 2 * dot(*this, n) * n; }

Vec3 Vec3::refract(const Vec3 &n, float ri) const {
  float d = dot(-(*this), n);
  d = std::fmin(d, 1);

  Vec3 a = ri * (*this + d * n);
  Vec3 b = -std::sqrt(std::fabs(1 - a.length2())) * n;

  return a + b;
}

Vec3 Vec3::rotate(const Vec3 &rotation) const {
  Vec3 v = *this;

  Vec2 yz(v.y, v.z);
  yz = yz.rotate(rotation.x);
  v = {v.x, yz.x, yz.y};

  Vec2 xz(v.x, v.z);
  xz = xz.rotate(rotation.y);
  v = {xz.x, v.y, xz.y};

  Vec2 xy(v.x, v.y);
  xy = xy.rotate(rotation.z);
  v = {xy.x, xy.y, v.z};

  return v;
}

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

Vec3 Vec3::operator+() const { return {x, y, z}; }
Vec3 Vec3::operator-() const { return {-x, -y, -z}; }

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

std::ostream &operator<<(std::ostream &os, const Vec3 &v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

Vec4 Vec4::getRandom() { return Vec4(getRandomFLoat(), getRandomFLoat(), getRandomFLoat(), getRandomFLoat()); }

float Vec4::length() const { return std::sqrt(length2()); }
float Vec4::length2() const { return x * x + y * y + z * z + w * w; }
float dot(const Vec4 &v1, const Vec4 &v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }

Vec4 normalize(const Vec4 &v) {
  Vec4 u = v / v.length();
  return u;
}

Vec4 Vec4::operator+() const { return {x, y, z, w}; }
Vec4 Vec4::operator-() const { return {-x, -y, -z, -w}; }

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

std::ostream &operator<<(std::ostream &os, const Vec4 &v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
  return os;
}
