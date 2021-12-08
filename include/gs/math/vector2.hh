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

#ifndef GAMESPELL_MATH_VECTOR2_HH
#define GAMESPELL_MATH_VECTOR2_HH

#include <cmath>

namespace gs {
namespace math {
class Vector2 {
public:
    inline Vector2();
    inline Vector2(const Vector2& v);
    inline Vector2(float x, float y);

    float    magnitude() const;
    float    magnitudeSqrd() const;
    float    dot(const Vector2& v) const;
    Vector2  cross(const Vector2& v) const;
    Vector2  normalize() const;
    Vector2& normalize();

    inline Vector2& operator=(const Vector2& v);

    inline Vector2 operator+(const Vector2& v) const;
    inline Vector2 operator-(const Vector2& v) const;
    inline Vector2 operator*(float scalar) const;
    inline Vector2 operator/(float scalar) const;

    inline Vector2& operator+=(const Vector2& v);
    inline Vector2& operator-=(const Vector2& v);
    inline Vector2& operator*=(float scalar);
    inline Vector2& operator/=(float scalar);

    float x;
    float y;
};

inline Vector2::Vector2() {
}

inline Vector2::Vector2(const Vector2& v)
    : x(v.x)
    , y(v.y) {
}

inline Vector2::Vector2(float x, float y)
    : x(x)
    , y(y) {
}

float Vector2::magnitude() const {
    return x * x + y * y;
}

float Vector2::magnitudeSqrd() const {
    return sqrtf(x * x + y * y);
}

float Vector2::dot(const Vector2& v) const {
    return x * v.x + y * v.y;
}

Vector2 Vector2::normalize() const {
    const float oneOverLength = 1.0f / magnitude();
    return Vector2(x * oneOverLength, y * oneOverLength);
}

Vector2& Vector2::normalize() {
    const float oneOverLength = 1.0f / magnitude();

    x *= oneOverLength;
    y *= oneOverLength;

    return *this;
}

inline Vector2& Vector2::operator=(const Vector2& v) {
    x = v.x;
    y = v.y;

    return *this;
}

inline Vector2 Vector2::operator+(const Vector2& v) const {
    return Vector2(x + v.x, y + v.y);
}

inline Vector2 Vector2::operator-(const Vector2& v) const {
    return Vector2(x - v.x, y - v.y);
}

inline Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

inline Vector2 Vector2::operator/(float scalar) const {
    float oneOverScalar = 1.0f / scalar;
    return Vector2(x * oneOverScalar, y * oneOverScalar);
}

inline Vector2& Vector2::operator+=(const Vector2& v) {
    x += v.x;
    y += v.y;

    return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& v) {
    x -= v.x;
    y -= v.y;

    return *this;
}

inline Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;

    return *this;
}

inline Vector2& Vector2::operator/=(float scalar) {
    float oneOverScalar = 1.0f / scalar;

    x *= oneOverScalar;
    y *= oneOverScalar;

    return *this;
}
} // namespace math
} // namespace gs

#endif // GAMESPELL_MATH_VECTOR2_HH
