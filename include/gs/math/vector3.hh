// Copyright 2021 addelajnen@outlook.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef GAMESPELL_MATH_VECTOR3_HH
#define GAMESPELL_MATH_VECTOR3_HH

#include <cmath>

namespace gs {
namespace math {
class Vector3 {
public:
    inline Vector3();
    inline Vector3(const Vector3& v);
    inline Vector3(float x, float y, float z);

    float    magnitude() const;
    float    magnitudeSqrd() const;
    float    dot(const Vector3& v) const;
    Vector3  cross(const Vector3& v) const;
    Vector3  normalize() const;
    Vector3& normalize();

    inline Vector3& operator=(const Vector3& v);

    inline Vector3 operator+(const Vector3& v) const;
    inline Vector3 operator-(const Vector3& v) const;
    inline Vector3 operator*(float scalar) const;
    inline Vector3 operator/(float scalar) const;

    inline Vector3& operator+=(const Vector3& v);
    inline Vector3& operator-=(const Vector3& v);
    inline Vector3& operator*=(float scalar);
    inline Vector3& operator/=(float scalar);

    float x;
    float y;
    float z;
};

inline Vector3::Vector3() {
}

inline Vector3::Vector3(const Vector3& v)
    : x(v.x)
    , y(v.y)
    , z(v.z) {
}

inline Vector3::Vector3(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z) {
}

float Vector3::magnitude() const {
    return x * x + y * y + z * z;
}

float Vector3::magnitudeSqrd() const {
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::dot(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const {
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3 Vector3::normalize() const {
    const float oneOverLength = 1.0f / magnitude();
    return Vector3(x * oneOverLength, y * oneOverLength, z * oneOverLength);
}

Vector3& Vector3::normalize() {
    const float oneOverLength = 1.0f / magnitude();

    x *= oneOverLength;
    y *= oneOverLength;
    z *= oneOverLength;

    return *this;
}

inline Vector3& Vector3::operator=(const Vector3& v) {
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

inline Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

inline Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

inline Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

inline Vector3 Vector3::operator/(float scalar) const {
    float oneOverScalar = 1.0f / scalar;
    return Vector3(x * oneOverScalar, y * oneOverScalar, z * oneOverScalar);
}

inline Vector3& Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

inline Vector3& Vector3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

inline Vector3& Vector3::operator/=(float scalar) {
    float oneOverScalar = 1.0f / scalar;

    x *= oneOverScalar;
    y *= oneOverScalar;
    z *= oneOverScalar;

    return *this;
}
} // namespace math
} // namespace gs

#endif // GAMESPELL_MATH_VECTOR3_HH
