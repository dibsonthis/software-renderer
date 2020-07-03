#include "math_functions.h"

int clamp_i(int value, int min, int max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

float clamp_f(float value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

float degToRad(float degree)
{
	float pi = 3.14159265359f;
	return degree * (pi / 180.0f);
}

float linearInterpolate_f(float a, float b, float percentage)
{
	float result = a + (b - a) * percentage;
	return result;
}

// Vector Maths

Vec3_f normalize_f(Vec3_f vector)
{
	double magnitude = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
	Vec3_f normalizedVector = { vector.x / magnitude, vector.y / magnitude, vector.z / magnitude };

	return normalizedVector;
}

Vec3_f scalarAdd_f(float num, Vec3_f vector)
{
	float x = vector.x + num; float y = vector.y + num; float z = vector.z + num;
	Vec3_f result = { x, y, z };
	return result;
}

Vec3_f scalarSubtract_f(float num, Vec3_f vector)
{
	float x = vector.x - num; float y = vector.y - num; float z = vector.z - num;
	Vec3_f result = { x, y, z };
	return result;
}

Vec3_f scalarMultiply_f(float num, Vec3_f vector)
{
	float x = vector.x * num; float y = vector.y * num; float z = vector.z * num;
	Vec3_f result = { x, y, z };
	return result;
}

Vec3_f addVectors_f(Vec3_f a, Vec3_f b)
{
	float x = a.x + b.x; float y = a.y + b.y; float z = a.z + b.z;
	Vec3_f result = { x, y, z };
	return result;
}

Vec3_f subVectors_f(Vec3_f a, Vec3_f b)
{
	float x = a.x - b.x; float y = a.y - b.y; float z = a.z - b.z;
	Vec3_f result = { x, y, z };
	return result;
}

Vec3_f mulVectors_f(Vec3_f a, Vec3_f b)
{
	float x = a.x * b.x; float y = a.y * b.y; float z = a.z * b.z;
	Vec3_f result = { x, y, z };
	return result;
}

float dot_f(Vec3_f a, Vec3_f b)
{
	float result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return result;
}

Vec3_f cross_f(Vec3_f a, Vec3_f b)
{
	float x = (a.y * b.z) - (a.z * b.y);
	float y = (a.z * b.x) - (a.x * b.z);
	float z = (a.x * b.y) - (a.y * b.x);
	Vec3_f result = { x, y, z };
	return result;
}

Vec3_f mat3_f(Vec3_f vector, Matrix3_f matrix)
{
	float x = (vector.x * matrix.a) + (vector.y * matrix.d) + (vector.z * matrix.g);
	float y = (vector.x * matrix.b) + (vector.y * matrix.e) + (vector.z * matrix.h);
	float z = (vector.x * matrix.c) + (vector.y * matrix.f) + (vector.z * matrix.i);
	Vec3_f result = { x, y, z };
	return result;
}

Vec4_f mat4_f(Vec4_f vector, Matrix4_f matrix)
{
	float x = (vector.x * matrix.a) + (vector.y * matrix.b) + (vector.z * matrix.c) + (vector.w * matrix.d);
	float y = (vector.x * matrix.e) + (vector.y * matrix.f) + (vector.z * matrix.g) + (vector.w * matrix.h);
	float z = (vector.x * matrix.i) + (vector.y * matrix.j) + (vector.z * matrix.k) + (vector.w * matrix.l);
	float w = (vector.x * matrix.m) + (vector.y * matrix.n) + (vector.z * matrix.o) + (vector.w * matrix.p);
	Vec4_f result = { x, y, z, w };
	return result;
}

// Matrix by Matrix multiplication

Matrix3_f mat3x3(Matrix3_f m1, Matrix3_f m2)
{
	float a = (m1.a * m2.a) + (m1.b * m2.d) + (m1.c * m2.g);
	float b = (m1.a * m2.b) + (m1.b * m2.e) + (m1.c * m2.h);
	float c = (m1.a * m2.c) + (m1.b * m2.f) + (m1.c * m2.i);

	float d = (m1.d * m2.a) + (m1.e * m2.d) + (m1.f * m2.g);
	float e = (m1.d * m2.b) + (m1.e * m2.e) + (m1.f * m2.h);
	float f = (m1.d * m2.c) + (m1.e * m2.f) + (m1.f * m2.i);

	float g = (m1.g * m2.a) + (m1.h * m2.d) + (m1.i * m2.g);
	float h = (m1.g * m2.b) + (m1.h * m2.e) + (m1.i * m2.h);
	float i = (m1.g * m2.c) + (m1.h * m2.f) + (m1.i * m2.i);

	Matrix3_f result =
	{
		a, b, c,
		d, e, f,
		g, h, i
	};

	return result;
}

Matrix4_f mat4x4(Matrix4_f m1, Matrix4_f m2)
{
	float a = (m1.a * m2.a) + (m1.b * m2.e) + (m1.c * m2.i) + (m1.d * m2.m);
	float b = (m1.a * m2.b) + (m1.b * m2.f) + (m1.c * m2.j) + (m1.d * m2.n);
	float c = (m1.a * m2.c) + (m1.b * m2.g) + (m1.c * m2.k) + (m1.d * m2.o);
	float d = (m1.a * m2.d) + (m1.b * m2.h) + (m1.c * m2.l) + (m1.d * m2.p);

	float e = (m1.e * m2.a) + (m1.f * m2.e) + (m1.g * m2.i) + (m1.h * m2.m);
	float f = (m1.e * m2.b) + (m1.f * m2.f) + (m1.g * m2.j) + (m1.h * m2.n);
	float g = (m1.e * m2.c) + (m1.f * m2.g) + (m1.g * m2.k) + (m1.h * m2.o);
	float h = (m1.e * m2.d) + (m1.f * m2.h) + (m1.g * m2.l) + (m1.h * m2.p);

	float i = (m1.i * m2.a) + (m1.j * m2.e) + (m1.k * m2.i) + (m1.l * m2.m);
	float j = (m1.i * m2.b) + (m1.j * m2.f) + (m1.k * m2.j) + (m1.l * m2.n);
	float k = (m1.i * m2.c) + (m1.j * m2.g) + (m1.k * m2.k) + (m1.l * m2.o);
	float l = (m1.i * m2.d) + (m1.j * m2.h) + (m1.k * m2.l) + (m1.l * m2.p);

	float m = (m1.m * m2.a) + (m1.n * m2.e) + (m1.o * m2.i) + (m1.p * m2.m);
	float n = (m1.m * m2.b) + (m1.n * m2.f) + (m1.o * m2.j) + (m1.p * m2.n);
	float o = (m1.m * m2.c) + (m1.n * m2.g) + (m1.o * m2.k) + (m1.p * m2.o);
	float p = (m1.m * m2.d) + (m1.n * m2.h) + (m1.o * m2.l) + (m1.p * m2.p);

	Matrix4_f result =
	{
		a, b, c, d,
		e, f, g, h,
		i, j, k, l,
		m, n, o, p
	};

	return result;
}