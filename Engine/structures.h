#pragma once

typedef struct Vec2_f { float x, y; } Vec2_f;
typedef struct Vec2_i { int x, y; } Vec2_i;

typedef struct Vec3_f { float x, y, z; } Vec3_f;
typedef struct Vec3_i { int x, y, z; } Vec3_i;

typedef struct Vec4_f { float x, y, z, w; } Vec4_f;
typedef struct Vec4_i { int x, y, z, w; } Vec4_i;

typedef struct Color { int r, g, b, a; } Color;

typedef struct Vertex
{

	Vec4_f vertexCoordinates;
	Vec2_f textureCoordinates;
	Vec3_f normalCoordinates;
	unsigned int indices;
	Color color;

} Vertex;

typedef struct Triangle { Vertex v1, v2, v3; } Triangle;


typedef struct Matrix3_f
{
	float a, b, c;
	float d, e, f;
	float g, h, i;

} Matrix3_f;

typedef struct Matrix4_f
{
	float a, b, c, d;
	float e, f, g, h;
	float i, j, k, l;
	float m, n, o, p;

} Matrix4_f;