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

#ifndef GAMESPELL_MATH_MATRIX4X4_HH
#define GAMESPELL_MATH_MATRIX4X4_HH

#include <cmath>

namespace gs {
namespace math {
class Matrix4x4 {
public:
    inline Matrix4x4();
    inline Matrix4x4(float m11,
                     float m12,
                     float m13,
                     float m14,
                     float m21,
                     float m22,
                     float m23,
                     float m24,
                     float m31,
                     float m32,
                     float m33,
                     float m34,
                     float m41,
                     float m42,
                     float m43,
                     float m44);
    inline Matrix4x4(const Matrix4x4& m);

    Matrix4x4& translate(float x, float y, float z);
    Matrix4x4& rotateXAxis(float radians);
    Matrix4x4& rotateYAxis(float radians);
    Matrix4x4& rotateZAxis(float radians);

    inline Matrix4x4& operator=(const Matrix4x4& m);

    inline Matrix4x4 operator*(const Matrix4x4& m) const;
    inline Matrix4x4 operator+(const Matrix4x4& m) const;
    inline Matrix4x4 operator-(const Matrix4x4& m) const;
    inline Matrix4x4 operator+(float scalar) const;
    inline Matrix4x4 operator-(float scalar) const;

    inline Matrix4x4& operator*=(const Matrix4x4& m);
    inline Matrix4x4& operator+=(const Matrix4x4& m);
    inline Matrix4x4& operator-=(const Matrix4x4& m);
    inline Matrix4x4& operator+=(float scalar);
    inline Matrix4x4& operator-=(float scalar);

    float m[16];
};

inline Matrix4x4::Matrix4x4() {
}

inline Matrix4x4::Matrix4x4(float m11,
                            float m12,
                            float m13,
                            float m14,
                            float m21,
                            float m22,
                            float m23,
                            float m24,
                            float m31,
                            float m32,
                            float m33,
                            float m34,
                            float m41,
                            float m42,
                            float m43,
                            float m44)
    : m{m11,
        m12,
        m13,
        m14,
        m21,
        m22,
        m23,
        m24,
        m31,
        m32,
        m33,
        m34,
        m41,
        m42,
        m43,
        m44} {
}

inline Matrix4x4::Matrix4x4(const Matrix4x4& other)
    : m{other.m[0],
        other.m[1],
        other.m[2],
        other.m[3],
        other.m[4],
        other.m[5],
        other.m[6],
        other.m[7],
        other.m[8],
        other.m[9],
        other.m[10],
        other.m[11],
        other.m[12],
        other.m[13],
        other.m[14],
        other.m[15]} {
}

inline Matrix4x4& Matrix4x4::translate(float x, float y, float z) {
    m[3]  = x;
    m[7]  = y;
    m[11] = z;

    return *this;
}

inline Matrix4x4& Matrix4x4::rotateXAxis(float radians) {
    float c = cosf(radians);
    float s = sinf(radians);

    m[5]  = c;
    m[6]  = -s;
    m[9]  = s;
    m[10] = c;

    return *this;
}

inline Matrix4x4& Matrix4x4::rotateYAxis(float radians) {
    float c = cosf(radians);
    float s = sinf(radians);

    m[0]  = +c;
    m[2]  = +s;
    m[8]  = -s;
    m[10] = c;

    return *this;
}

inline Matrix4x4& Matrix4x4::rotateZAxis(float radians) {
    float c = cosf(radians);
    float s = sinf(radians);

    m[0] = c;
    m[1] = -s;
    m[4] = s;
    m[5] = c;

    return *this;
}

inline Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) {
    m[0]  = other.m[0];
    m[1]  = other.m[1];
    m[2]  = other.m[2];
    m[3]  = other.m[3];
    m[4]  = other.m[4];
    m[5]  = other.m[5];
    m[6]  = other.m[6];
    m[7]  = other.m[7];
    m[8]  = other.m[8];
    m[9]  = other.m[9];
    m[10] = other.m[10];
    m[11] = other.m[11];
    m[12] = other.m[12];
    m[13] = other.m[13];
    m[14] = other.m[14];
    m[15] = other.m[15];

    return *this;
}

inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    return Matrix4x4(m[0] * other.m[0] + m[1] * other.m[4] + m[2] * other.m[8] +
                         m[3] * other.m[12],
                     m[0] * other.m[1] + m[1] * other.m[5] + m[2] * other.m[9] +
                         m[3] * other.m[13],
                     m[0] * other.m[2] + m[1] * other.m[6] +
                         m[2] * other.m[10] + m[3] * other.m[14],
                     m[0] * other.m[3] + m[1] * other.m[7] +
                         m[2] * other.m[11] + m[3] * other.m[15],
                     m[4] * other.m[0] + m[5] * other.m[4] + m[6] * other.m[8] +
                         m[7] * other.m[12],
                     m[4] * other.m[1] + m[5] * other.m[5] + m[6] * other.m[9] +
                         m[7] * other.m[13],
                     m[4] * other.m[2] + m[5] * other.m[6] +
                         m[6] * other.m[10] + m[7] * other.m[14],
                     m[4] * other.m[3] + m[5] * other.m[7] +
                         m[6] * other.m[11] + m[7] * other.m[15],
                     m[8] * other.m[0] + m[9] * other.m[4] +
                         m[10] * other.m[8] + m[11] * other.m[12],
                     m[8] * other.m[1] + m[9] * other.m[5] +
                         m[10] * other.m[9] + m[11] * other.m[13],
                     m[8] * other.m[2] + m[9] * other.m[6] +
                         m[10] * other.m[10] + m[11] * other.m[14],
                     m[8] * other.m[3] + m[9] * other.m[7] +
                         m[10] * other.m[11] + m[11] * other.m[15],
                     m[12] * other.m[0] + m[13] * other.m[4] +
                         m[14] * other.m[8] + m[15] * other.m[12],
                     m[12] * other.m[1] + m[13] * other.m[5] +
                         m[14] * other.m[9] + m[15] * other.m[13],
                     m[12] * other.m[2] + m[13] * other.m[6] +
                         m[14] * other.m[10] + m[15] * other.m[14],
                     m[12] * other.m[3] + m[13] * other.m[7] +
                         m[14] * other.m[11] + m[15] * other.m[15]);
}

inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
    return Matrix4x4(m[0] + other.m[0],
                     m[1] + other.m[1],
                     m[2] + other.m[2],
                     m[3] + other.m[3],
                     m[4] + other.m[4],
                     m[5] + other.m[5],
                     m[6] + other.m[6],
                     m[7] + other.m[7],
                     m[8] + other.m[8],
                     m[9] + other.m[9],
                     m[10] + other.m[10],
                     m[11] + other.m[11],
                     m[12] + other.m[12],
                     m[13] + other.m[13],
                     m[14] + other.m[14],
                     m[15] + other.m[15]);
}

inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const {
    return Matrix4x4(m[0] - other.m[0],
                     m[1] - other.m[1],
                     m[2] - other.m[2],
                     m[3] - other.m[3],
                     m[4] - other.m[4],
                     m[5] - other.m[5],
                     m[6] - other.m[6],
                     m[7] - other.m[7],
                     m[8] - other.m[8],
                     m[9] - other.m[9],
                     m[10] - other.m[10],
                     m[11] - other.m[11],
                     m[12] - other.m[12],
                     m[13] - other.m[13],
                     m[14] - other.m[14],
                     m[15] - other.m[15]);
}

inline Matrix4x4 Matrix4x4::operator+(float scalar) const {
    return Matrix4x4(m[0] + scalar,
                     m[1] + scalar,
                     m[2] + scalar,
                     m[3] + scalar,
                     m[4] + scalar,
                     m[5] + scalar,
                     m[6] + scalar,
                     m[7] + scalar,
                     m[8] + scalar,
                     m[9] + scalar,
                     m[10] + scalar,
                     m[11] + scalar,
                     m[12] + scalar,
                     m[13] + scalar,
                     m[14] + scalar,
                     m[15] + scalar);
}

inline Matrix4x4 Matrix4x4::operator-(float scalar) const {
    return Matrix4x4(m[0] - scalar,
                     m[1] - scalar,
                     m[2] - scalar,
                     m[3] - scalar,
                     m[4] - scalar,
                     m[5] - scalar,
                     m[6] - scalar,
                     m[7] - scalar,
                     m[8] - scalar,
                     m[9] - scalar,
                     m[10] - scalar,
                     m[11] - scalar,
                     m[12] - scalar,
                     m[13] - scalar,
                     m[14] - scalar,
                     m[15] - scalar);
}

inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {

    const float m11 = m[0] * other.m[0] + m[1] * other.m[4] +
                      m[2] * other.m[8] + m[3] * other.m[12];
    const float m12 = m[0] * other.m[1] + m[1] * other.m[5] +
                      m[2] * other.m[9] + m[3] * other.m[13];
    const float m13 = m[0] * other.m[2] + m[1] * other.m[6] +
                      m[2] * other.m[10] + m[3] * other.m[14];
    const float m14 = m[0] * other.m[3] + m[1] * other.m[7] +
                      m[2] * other.m[11] + m[3] * other.m[15];
    const float m21 = m[4] * other.m[0] + m[5] * other.m[4] +
                      m[6] * other.m[8] + m[7] * other.m[12];
    const float m22 = m[4] * other.m[1] + m[5] * other.m[5] +
                      m[6] * other.m[9] + m[7] * other.m[13];
    const float m23 = m[4] * other.m[2] + m[5] * other.m[6] +
                      m[6] * other.m[10] + m[7] * other.m[14];
    const float m24 = m[4] * other.m[3] + m[5] * other.m[7] +
                      m[6] * other.m[11] + m[7] * other.m[15];
    const float m31 = m[8] * other.m[0] + m[9] * other.m[4] +
                      m[10] * other.m[8] + m[11] * other.m[12];
    const float m32 = m[8] * other.m[1] + m[9] * other.m[5] +
                      m[10] * other.m[9] + m[11] * other.m[13];
    const float m33 = m[8] * other.m[2] + m[9] * other.m[6] +
                      m[10] * other.m[10] + m[11] * other.m[14];
    const float m34 = m[8] * other.m[3] + m[9] * other.m[7] +
                      m[10] * other.m[11] + m[11] * other.m[15];
    const float m41 = m[12] * other.m[0] + m[13] * other.m[4] +
                      m[14] * other.m[8] + m[15] * other.m[12];
    const float m42 = m[12] * other.m[1] + m[13] * other.m[5] +
                      m[14] * other.m[9] + m[15] * other.m[13];
    const float m43 = m[12] * other.m[2] + m[13] * other.m[6] +
                      m[14] * other.m[10] + m[15] * other.m[14];
    const float m44 = m[12] * other.m[3] + m[13] * other.m[7] +
                      m[14] * other.m[11] + m[15] * other.m[15];

    m[0]  = m11;
    m[1]  = m12;
    m[2]  = m13;
    m[3]  = m14;
    m[4]  = m21;
    m[5]  = m22;
    m[6]  = m23;
    m[7]  = m24;
    m[8]  = m31;
    m[9]  = m32;
    m[10] = m33;
    m[11] = m34;
    m[12] = m41;
    m[13] = m42;
    m[14] = m43;
    m[15] = m44;

    return *this;
}

inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& o) {
    m[0] += o.m[0];
    m[1] += o.m[1];
    m[2] += o.m[2];
    m[3] += o.m[3];
    m[4] += o.m[4];
    m[5] += o.m[5];
    m[6] += o.m[6];
    m[7] += o.m[7];
    m[8] += o.m[8];
    m[9] += o.m[9];
    m[10] += o.m[10];
    m[11] += o.m[11];
    m[12] += o.m[12];
    m[13] += o.m[13];
    m[14] += o.m[14];
    m[15] += o.m[15];

    return *this;
}

inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& o) {
    m[0] -= o.m[0];
    m[1] -= o.m[1];
    m[2] -= o.m[2];
    m[3] -= o.m[3];
    m[4] -= o.m[4];
    m[5] -= o.m[5];
    m[6] -= o.m[6];
    m[7] -= o.m[7];
    m[8] -= o.m[8];
    m[9] -= o.m[9];
    m[10] -= o.m[10];
    m[11] -= o.m[11];
    m[12] -= o.m[12];
    m[13] -= o.m[13];
    m[14] -= o.m[14];
    m[15] -= o.m[15];

    return *this;
}

inline Matrix4x4& Matrix4x4::operator+=(float scalar) {
    m[0] += scalar;
    m[1] += scalar;
    m[2] += scalar;
    m[3] += scalar;
    m[4] += scalar;
    m[5] += scalar;
    m[6] += scalar;
    m[7] += scalar;
    m[8] += scalar;
    m[9] += scalar;
    m[10] += scalar;
    m[11] += scalar;
    m[12] += scalar;
    m[13] += scalar;
    m[14] += scalar;
    m[15] += scalar;

    return *this;
}

inline Matrix4x4& Matrix4x4::operator-=(float scalar) {
    m[0] -= scalar;
    m[1] -= scalar;
    m[2] -= scalar;
    m[3] -= scalar;
    m[4] -= scalar;
    m[5] -= scalar;
    m[6] -= scalar;
    m[7] -= scalar;
    m[8] -= scalar;
    m[9] -= scalar;
    m[10] -= scalar;
    m[11] -= scalar;
    m[12] -= scalar;
    m[13] -= scalar;
    m[14] -= scalar;
    m[15] -= scalar;

    return *this;
}

} // namespace math
} // namespace gs

#endif // GAMESPELL_MATH_MATRIX4X4_HH
