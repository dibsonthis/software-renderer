#pragma once

#include <math.h>
#include "structures.h"

// Helper Functions

int clamp_i (int value, int min, int max);
float clamp_f(float value, float min, float max);
float degToRad(float degree);
float linearInterpolate_f(float a, float b, float percentage);

// Vector Maths

Vec3_f normalize_f(Vec3_f vector);
Vec3_f scalarAdd_f(float num, Vec3_f vector);
Vec3_f scalarSubtract_f(float num, Vec3_f vector);
Vec3_f scalarMultiply_f(float num, Vec3_f vector);
Vec3_f addVectors_f(Vec3_f a, Vec3_f b);
Vec3_f subVectors_f(Vec3_f a, Vec3_f b);
Vec3_f mulVectors_f(Vec3_f a, Vec3_f b);
float dot_f(Vec3_f a, Vec3_f b);
Vec3_f cross_f(Vec3_f a, Vec3_f b);

// Matrix by Vector Multiplication

Vec3_f mat3_f(Vec3_f vector, Matrix3_f matrix);
Vec4_f mat4_f(Vec4_f vector, Matrix4_f matrix);

// Matrix by Matrix Multiplication

Matrix3_f mat3x3(Matrix3_f m1, Matrix3_f m2);
Matrix4_f mat4x4(Matrix4_f m1, Matrix4_f m2);

