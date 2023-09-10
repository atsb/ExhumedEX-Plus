//
// Copyright(C) 2014-2015 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//      Matrix (left handed) operations
//
// Reference:
// _________________
// | 0   4   8   12 |
// | 1   5   9   13 |
// | 2   6  10   14 |
// | 3   7  11   15 |
// _________________
//
// translation
// _________________
// | 0   4   8   x  |
// | 1   5   9   y  |
// | 2   6  10   z  |
// | 3   7  11   15 |
// _________________
//
// rotation x
// _________________
// |(1)  4   8   x  |
// | 1   xc -xs  y  |
// | 2   xs  xs  z  |
// | 3   7  11  (1) |
// _________________
//
// rotation y
// _________________
// | yc  4  ys   12 |
// | 1  (1)  9   13 |
// |-ys  6  yc   14 |
// | 3   7  11  (1) |
// _________________
//
// rotation z
// _________________
// | zc -zs  8   12 |
// | zs  zc  9   13 |
// | 2   6  (1)  14 |
// | 3   7  11  (1) |
// _________________
//

#include <string.h>
#include "mathlib.h"

//
// kexMatrix::kexMatrix
//

kexMatrix::kexMatrix(void)
{
    Identity();
}

//
// kexMatrix::kexMatrix
//

kexMatrix::kexMatrix(const kexMatrix &mtx)
{
    for(int i = 0; i < 4; i++)
    {
        vectors[i].x = mtx.vectors[i].x;
        vectors[i].y = mtx.vectors[i].y;
        vectors[i].z = mtx.vectors[i].z;
        vectors[i].w = mtx.vectors[i].w;
    }
}

//
// kexMatrix::kexMatrix
//

kexMatrix::kexMatrix(const float x, const float y, const float z)
{
    Identity(x, y, z);
}

//
// kexMatrix::kexMatrix
//

kexMatrix::kexMatrix(const kexQuat &quat)
{
    float xx = quat.x * quat.x;
    float yx = quat.y * quat.x;
    float zx = quat.z * quat.x;
    float wx = quat.w * quat.x;
    float yy = quat.y * quat.y;
    float zy = quat.z * quat.y;
    float wy = quat.w * quat.y;
    float zz = quat.z * quat.z;
    float wz = quat.w * quat.z;
    float ww = quat.w * quat.w;

    vectors[0].Set(
        ((ww + xx) - yy) - zz,
        (wz + wz) + (yx + yx),
        (zx + zx) - (wy + wy),
        0);
    vectors[1].Set(
        (yx + yx) - (wz + wz),
        (yy + (ww - xx)) - zz,
        (wx + wx) + (zy + zy),
        0);
    vectors[2].Set(
        (wy + wy + zx + zx),
        (zy + zy) - (wx + wx),
        ((ww - xx) - yy) + zz,
        0);
    vectors[3].Set(0, 0, 0, 1);
}

//
// kexMatrix::kexMatrix
//

kexMatrix::kexMatrix(const float angle, const int axis)
{
    float s;
    float c;

    s = kexMath::Sin(angle);
    c = kexMath::Cos(angle);

    Identity();

    switch(axis)
    {
    case 0:
        this->vectors[0].x = c;
        this->vectors[0].z = -s;
        this->vectors[3].x = s;
        this->vectors[3].z = c;
        break;
    case 1:
        this->vectors[1].y = c;
        this->vectors[1].z = s;
        this->vectors[2].y = -s;
        this->vectors[2].z = c;
        break;
    case 2:
        this->vectors[0].x = c;
        this->vectors[0].y = s;
        this->vectors[1].x = -s;
        this->vectors[1].y = c;
        break;
    }
}

//
// kexMatrix::Identity
//

kexMatrix &kexMatrix::Identity(void)
{
    vectors[0].Set(1, 0, 0, 0);
    vectors[1].Set(0, 1, 0, 0);
    vectors[2].Set(0, 0, 1, 0);
    vectors[3].Set(0, 0, 0, 1);

    return *this;
}

//
// kexMatrix::Identity
//

kexMatrix &kexMatrix::Identity(const float x, const float y, const float z)
{
    vectors[0].Set(x, 0, 0, 0);
    vectors[1].Set(0, y, 0, 0);
    vectors[2].Set(0, 0, z, 0);
    vectors[3].Set(0, 0, 0, 1);

    return *this;
}

//
// kexMatrix::SetTranslation
//

kexMatrix &kexMatrix::SetTranslation(const float x, const float y, const float z)
{
    vectors[3].ToVec3().Set(x, y, z);
    return *this;
}

//
// kexMatrix::SetTranslation
//

kexMatrix &kexMatrix::SetTranslation(const kexVec3 &vector)
{
    vectors[3].ToVec3() = vector;
    return *this;
}

//
// kexMatrix::AddTranslation
//

kexMatrix &kexMatrix::AddTranslation(const float x, const float y, const float z)
{
    vectors[3].x += x;
    vectors[3].y += y;
    vectors[3].z += z;
    return *this;
}

//
// kexMatrix::AddTranslation
//

kexMatrix &kexMatrix::AddTranslation(const kexVec3 &vector)
{
    vectors[3].ToVec3() += vector;
    return *this;
}

//
// kexMatrix::Scale
//

kexMatrix &kexMatrix::Scale(const float x, const float y, const float z)
{
    vectors[0].ToVec3() *= x;
    vectors[1].ToVec3() *= y;
    vectors[2].ToVec3() *= z;

    return *this;
}

//
// kexMatrix::Scale
//

kexMatrix &kexMatrix::Scale(const kexVec3 &vector)
{
    vectors[0].ToVec3() *= vector.x;
    vectors[1].ToVec3() *= vector.y;
    vectors[2].ToVec3() *= vector.z;

    return *this;
}

//
// kexMatrix::Scale
//

kexMatrix kexMatrix::Scale(const kexMatrix &mtx, const float x, const float y, const float z)
{
    kexMatrix out;

    out.vectors[0].ToVec3() = mtx.vectors[0].ToVec3() * x;
    out.vectors[1].ToVec3() = mtx.vectors[1].ToVec3() * y;
    out.vectors[2].ToVec3() = mtx.vectors[2].ToVec3() * z;

    return out;
}

//
// kexMatrix::RotateX
//

void kexMatrix::RotateX(float angle)
{
    float s;
    float c;
    float tm1;
    float tm5;
    float tm9;
    float tm13;

    s = kexMath::Sin(angle);
    c = kexMath::Cos(angle);

    tm1     = vectors[0].y;
    tm5     = vectors[1].y;
    tm9     = vectors[2].y;
    tm13    = vectors[3].y;

    vectors[0].y = tm1  * c - s * vectors[0].z;
    vectors[0].z = c * vectors[0].z + tm1  * s;
    vectors[1].y = tm5  * c - s * vectors[1].z;
    vectors[1].z = c * vectors[1].z + tm5  * s;
    vectors[2].y = tm9  * c - s * vectors[2].z;
    vectors[2].z = c * vectors[2].z + tm9  * s;
    vectors[3].y = tm13 * c - s * vectors[3].z;
    vectors[3].z = c * vectors[3].z + tm13 * s;
}

//
// kexMatrix::RotateY
//

void kexMatrix::RotateY(float angle)
{
    float s;
    float c;
    float tm0;
    float tm1;
    float tm2;

    s = kexMath::Sin(angle);
    c = kexMath::Cos(angle);

    tm0     = vectors[0].x;
    tm1     = vectors[0].y;
    tm2     = vectors[0].z;

    vectors[0].x = tm0 * c - s * vectors[2].x;
    vectors[2].x = c * vectors[2].x + tm0 * s;
    vectors[0].y = tm1 * c - s * vectors[2].y;
    vectors[2].y = c * vectors[2].y + tm1 * s;
    vectors[0].z = tm2 * c - s * vectors[2].z;
    vectors[2].z = c * vectors[2].z + tm2 * s;
}

//
// kexMatrix::RotateZ
//

void kexMatrix::RotateZ(float angle)
{
    float s;
    float c;
    float tm0;
    float tm8;
    float tm4;
    float tm12;

    s = kexMath::Sin(angle);
    c = kexMath::Cos(angle);

    tm0     = vectors[0].x;
    tm4     = vectors[1].x;
    tm8     = vectors[2].x;
    tm12    = vectors[3].x;

    vectors[0].x = s * vectors[0].z + tm0  * c;
    vectors[0].z = c * vectors[0].z - tm0  * s;
    vectors[1].x = s * vectors[1].z + tm4  * c;
    vectors[1].z = c * vectors[1].z - tm4  * s;
    vectors[2].x = s * vectors[2].z + tm8  * c;
    vectors[2].z = c * vectors[2].z - tm8  * s;
    vectors[3].x = s * vectors[3].z + tm12 * c;
    vectors[3].z = c * vectors[3].z - tm12 * s;
}

//
// kexMatrix::Transpose
//

kexMatrix &kexMatrix::Transpose(void)
{
    kexVec3 v1 = vectors[1].ToVec3();
    kexVec3 v2 = vectors[2].ToVec3();

    vectors[1].ToVec3() = v2;
    vectors[2].ToVec3() = v1;
    return *this;
}

//
// kexMatrix::Transpose
//

kexMatrix kexMatrix::Transpose(const kexMatrix &mtx)
{
    kexMatrix out;

    out.vectors[0].ToVec3() = mtx.vectors[0].ToVec3();
    out.vectors[1].ToVec3() = mtx.vectors[2].ToVec3();
    out.vectors[2].ToVec3() = mtx.vectors[1].ToVec3();
    out.vectors[3].ToVec3() = mtx.vectors[3].ToVec3();

    return out;
}

//
// kexMatrix::Invert
//

kexMatrix kexMatrix::Invert(kexMatrix &mtx)
{
    float d;
    float *m;

    m = mtx.ToFloatPtr();

    d = m[ 0] * m[10] * m[ 5] -
        m[ 0] * m[ 9] * m[ 6] -
        m[ 1] * m[ 4] * m[10] +
        m[ 2] * m[ 4] * m[ 9] +
        m[ 1] * m[ 6] * m[ 8] -
        m[ 2] * m[ 5] * m[ 8];

    if(d != 0.0f)
    {
        kexMatrix inv;

        d = (1.0f / d);

        inv.vectors[0].x = (  m[10] * m[ 5] - m[ 9] * m[ 6]) * d;
        inv.vectors[0].y = -((m[ 1] * m[10] - m[ 2] * m[ 9]) * d);
        inv.vectors[0].z = (  m[ 1] * m[ 6] - m[ 2] * m[ 5]) * d;
        inv.vectors[0].w = 0;
        inv.vectors[1].x = (  m[ 6] * m[ 8] - m[ 4] * m[10]) * d;
        inv.vectors[1].y = (  m[ 0] * m[10] - m[ 2] * m[ 8]) * d;
        inv.vectors[1].z = -((m[ 0] * m[ 6] - m[ 2] * m[ 4]) * d);
        inv.vectors[1].w = 0;
        inv.vectors[2].x = -((m[ 5] * m[ 8] - m[ 4] * m[ 9]) * d);
        inv.vectors[2].y = (  m[ 1] * m[ 8] - m[ 0] * m[ 9]) * d;
        inv.vectors[2].z = -((m[ 1] * m[ 4] - m[ 0] * m[ 5]) * d);
        inv.vectors[2].w = 0;
        inv.vectors[3].x = (
                               ( m[13] * m[10] - m[14] * m[ 9]) * m[ 4]
                               + m[14] * m[ 5] * m[ 8]
                               - m[13] * m[ 6] * m[ 8]
                               - m[12] * m[10] * m[ 5]
                               + m[12] * m[ 9] * m[ 6]) * d;
        inv.vectors[3].y = (
                               m[ 0] * m[14] * m[ 9]
                               - m[ 0] * m[13] * m[10]
                               - m[14] * m[ 1] * m[ 8]
                               + m[13] * m[ 2] * m[ 8]
                               + m[12] * m[ 1] * m[10]
                               - m[12] * m[ 2] * m[ 9]) * d;
        inv.vectors[3].z = -(
                               ( m[ 0] * m[14] * m[ 5]
                                 - m[ 0] * m[13] * m[ 6]
                                 - m[14] * m[ 1] * m[ 4]
                                 + m[13] * m[ 2] * m[ 4]
                                 + m[12] * m[ 1] * m[ 6]
                                 - m[12] * m[ 2] * m[ 5]) * d);
        inv.vectors[3].w = 1.0f;

        return inv;
    }

    return mtx;
}

//
// kexMatrix::SetViewProjection
//

void kexMatrix::SetViewProjection(float aspect, float fov, float zNear, float zFar)
{
    float top       = zNear * kexMath::Tan(fov * kexMath::pi / 360.0f);
    float bottom    = -top;
    float left      = bottom * aspect;
    float right     = top * aspect;

    vectors[0].x =  (2 * zNear) / (right - left);
    vectors[1].y =  (2 * zNear) / (top - bottom);
    vectors[3].z = -(2 * zFar * zNear) / (zFar - zNear);

    vectors[2].x =  (right + left) / (right - left);
    vectors[2].y =  (top + bottom) / (top - bottom);
    vectors[2].z = -(zFar + zNear) / (zFar - zNear);

    vectors[0].y = 0;
    vectors[0].z = 0;
    vectors[0].w = 0;
    vectors[1].x = 0;
    vectors[1].w = 0;
    vectors[1].z = 0;
    vectors[2].w = -1;
    vectors[3].x = 0;
    vectors[3].y = 0;
    vectors[3].w = 0;
}

//
// kexMatrix::SetOrtho
//

void kexMatrix::SetOrtho(float left, float right,
                         float bottom, float top,
                         float zNear, float zFar)
{
    vectors[0].x =  2 / (right - left);
    vectors[1].y =  2 / (top - bottom);
    vectors[2].z = -2 / (zFar - zNear);

    vectors[3].x = -(right + left) / (right - left);
    vectors[3].y = -(top + bottom) / (top - bottom);
    vectors[3].z = -(zFar + zNear) / (zFar - zNear);
    vectors[3].w = 1;

    vectors[0].y = 0;
    vectors[0].z = 0;
    vectors[0].w = 0;
    vectors[1].x = 0;
    vectors[1].z = 0;
    vectors[1].w = 0;
    vectors[2].x = 0;
    vectors[2].y = 0;
    vectors[2].w = 0;
}

//
// kexMatrix::ToQuat
//

kexQuat kexMatrix::ToQuat(void)
{
    float t;
    float d;
    float mx;
    float my;
    float mz;
    float m21;
    float m20;
    float m10;
    kexQuat q;

    mx = vectors[0][0];
    my = vectors[1][1];
    mz = vectors[2][2];

    m21 = (vectors[2][1] - vectors[1][2]);
    m20 = (vectors[2][0] - vectors[0][2]);
    m10 = (vectors[1][0] - vectors[0][1]);

    t = 1.0f + mx + my + mz;

    if(t > 0)
    {
        d = 0.5f / kexMath::Sqrt(t);
        q.x = m21 * d;
        q.y = m20 * d;
        q.z = m10 * d;
        q.w = 0.25f / d;
    }
    else if(mx > my && mx > mz)
    {
        d = kexMath::Sqrt(1.0f + mx - my - mz) * 2;
        q.x = 0.5f / d;
        q.y = m10 / d;
        q.z = m20 / d;
        q.w = m21 / d;
    }
    else if(my > mz)
    {
        d = kexMath::Sqrt(1.0f + my - mx - mz) * 2;
        q.x = m10 / d;
        q.y = 0.5f / d;
        q.z = m21 / d;
        q.w = m20 / d;
    }
    else
    {
        d = kexMath::Sqrt(1.0f + mz - mx - my) * 2;
        q.x = m20 / d;
        q.y = m21 / d;
        q.z = 0.5f / d;
        q.w = m10 / d;
    }

    q.Normalize();
    return q;
}

//
// kexMatrix::operator*
//

kexMatrix kexMatrix::operator*(const kexVec3 &vector)
{
    kexMatrix out(*this);

    out.vectors[3].ToVec3() +=
        vectors[0].ToVec3() * vector.x +
        vectors[1].ToVec3() * vector.y +
        vectors[2].ToVec3() * vector.z;
    return out;
}

//
// kexMatrix::operator*=
//

kexMatrix &kexMatrix::operator*=(const kexVec3 &vector)
{
    vectors[3].ToVec3() +=
        vectors[0].ToVec3() * vector.x +
        vectors[1].ToVec3() * vector.y +
        vectors[2].ToVec3() * vector.z;
    return *this;
}

//
// kexMatrix::ToFloatPtr
//

float *kexMatrix::ToFloatPtr(void)
{
    return reinterpret_cast<float*>(vectors);
}

//
// kexMatrix::operator*
//

kexMatrix kexMatrix::operator*(const kexMatrix &matrix)
{
    kexMatrix out;

    for(int i = 0; i < 4; i++)
    {
        out.vectors[i].x =
            vectors[i].x * matrix.vectors[0].x +
            vectors[i].y * matrix.vectors[1].x +
            vectors[i].z * matrix.vectors[2].x +
            vectors[i].w * matrix.vectors[3].x;
        out.vectors[i].y =
            vectors[i].x * matrix.vectors[0].y +
            vectors[i].y * matrix.vectors[1].y +
            vectors[i].z * matrix.vectors[2].y +
            vectors[i].w * matrix.vectors[3].y;
        out.vectors[i].z =
            vectors[i].x * matrix.vectors[0].z +
            vectors[i].y * matrix.vectors[1].z +
            vectors[i].z * matrix.vectors[2].z +
            vectors[i].w * matrix.vectors[3].z;
        out.vectors[i].w =
            vectors[i].x * matrix.vectors[0].w +
            vectors[i].y * matrix.vectors[1].w +
            vectors[i].z * matrix.vectors[2].w +
            vectors[i].w * matrix.vectors[3].w;
    }

    return out;
}

//
// kexMatrix::operator*
//

kexMatrix operator*(const kexMatrix &m1, const kexMatrix &m2)
{
    kexMatrix out;

    for(int i = 0; i < 4; i++)
    {
        out.vectors[i].x =
            m1.vectors[i].x * m2.vectors[0].x +
            m1.vectors[i].y * m2.vectors[1].x +
            m1.vectors[i].z * m2.vectors[2].x +
            m1.vectors[i].w * m2.vectors[3].x;
        out.vectors[i].y =
            m1.vectors[i].x * m2.vectors[0].y +
            m1.vectors[i].y * m2.vectors[1].y +
            m1.vectors[i].z * m2.vectors[2].y +
            m1.vectors[i].w * m2.vectors[3].y;
        out.vectors[i].z =
            m1.vectors[i].x * m2.vectors[0].z +
            m1.vectors[i].y * m2.vectors[1].z +
            m1.vectors[i].z * m2.vectors[2].z +
            m1.vectors[i].w * m2.vectors[3].z;
        out.vectors[i].w =
            m1.vectors[i].x * m2.vectors[0].w +
            m1.vectors[i].y * m2.vectors[1].w +
            m1.vectors[i].z * m2.vectors[2].w +
            m1.vectors[i].w * m2.vectors[3].w;
    }

    return out;
}

//
// kexMatrix::operator|
//

kexMatrix kexMatrix::operator|(const kexMatrix &matrix)
{
    kexMatrix out;

    for(int i = 0; i < 3; i++)
    {
        out.vectors[i].x =
            vectors[i].x * matrix.vectors[0].x +
            vectors[i].y * matrix.vectors[1].x +
            vectors[i].z * matrix.vectors[2].x;
        out.vectors[i].y =
            vectors[i].x * matrix.vectors[0].y +
            vectors[i].y * matrix.vectors[1].y +
            vectors[i].z * matrix.vectors[2].y;
        out.vectors[i].z =
            vectors[i].x * matrix.vectors[0].z +
            vectors[i].y * matrix.vectors[1].z +
            vectors[i].z * matrix.vectors[2].z;
    }

    out.vectors[3].x =
        vectors[3].x * matrix.vectors[0].x +
        vectors[3].y * matrix.vectors[1].x +
        vectors[3].z * matrix.vectors[2].x + matrix.vectors[3].x;
    out.vectors[3].y =
        vectors[3].x * matrix.vectors[0].y +
        vectors[3].y * matrix.vectors[1].y +
        vectors[3].z * matrix.vectors[2].y + matrix.vectors[3].y;
    out.vectors[3].z =
        vectors[3].x * matrix.vectors[0].z +
        vectors[3].y * matrix.vectors[1].z +
        vectors[3].z * matrix.vectors[2].z + matrix.vectors[3].z;

    return out;
}

//
// kexMatrix::operator=
//

kexMatrix &kexMatrix::operator=(const kexMatrix &matrix)
{
    vectors[0] = matrix.vectors[0];
    vectors[1] = matrix.vectors[1];
    vectors[2] = matrix.vectors[2];
    vectors[3] = matrix.vectors[3];

    return *this;
}

//
// kexMatrix::operator=
//

kexMatrix &kexMatrix::operator=(const float *m)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            vectors[i][j] = m[i * 4 + j];
        }
    }

    return *this;
}
