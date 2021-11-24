#pragma once
#include <math.h>
#include <cmath>
#include <algorithm>
#include "FastNoise.h"

#pragma region Vec2

struct Vec2
{
	float x;
	float y;

	Vec2();
	Vec2(float a, float b);
	float Dot(Vec2 vec);
	Vec2 Cross(Vec2 vec);
	float Magnitude();
	float MagnitudeSqr();
	void Normalise();
	Vec2 GetNormalised();
	float Distance(Vec2 target);
};

Vec2 operator/(Vec2 vec, float divide);
Vec2 operator/=(Vec2& vec, float divide);
Vec2 operator*(Vec2 vec, float mult);
Vec2 operator*=(Vec2& vec, float mult);
Vec2 operator+(Vec2 vec, Vec2 add);
Vec2 operator+=(Vec2& vec, Vec2 add);
Vec2 operator-(Vec2 vec, Vec2 subtract);
Vec2 operator-=(Vec2 & vec, Vec2 subtract);

#pragma endregion

#pragma region Vec3

struct Vec3
{
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float a, float b, float c);
	float Dot(Vec3 vec);
	float Magnitude();
	float MagnitudeSqr();
	void Normalise();
	Vec3 GetNormalised();
	float Distance(Vec3 target);
};

Vec3 operator/(Vec3 vec, float divide);
Vec3 operator/=(Vec3& vec, float divide);
Vec3 operator*(Vec3 vec, float mult);
Vec3 operator*=(Vec3& vec, float mult);
Vec3 operator+(Vec3 vec, Vec3 add);
Vec3 operator+=(Vec3& vec, Vec3 add);
Vec3 operator-(Vec3 vec, Vec3 subtract);
Vec3 operator-=(Vec3& vec, Vec3 subtract);

#pragma endregion

#pragma region Vec4
struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	Vec4();
	Vec4(float a, float b, float c, float d);
	Vec4(Vec2 a, Vec2 b);
	float Dot(Vec4 vec);
	float Magnitude();
	float MagnitudeSqr();
	void Normalise();
	Vec4 GetNormalised();
	float Distance(Vec4 target);
};

Vec4 operator/(Vec4 vec, float divide);
Vec4 operator/=(Vec4& vec, float divide);
Vec4 operator*(Vec4 vec, float mult);
Vec4 operator*=(Vec4& vec, float mult);
Vec4 operator+(Vec4 vec, Vec4 add);
Vec4 operator+=(Vec4& vec, Vec4 add);
Vec4 operator-(Vec4 vec, Vec4 subtract);
Vec4 operator-=(Vec4& vec, Vec4 subtract);

#pragma endregion

float Max(float a, float b);
float Min(float a, float b);
float Abs(float value);
float Clamp(float value, float lower, float upper);
float RandomFloat(float a, float b);
float InverseLerp(float xx, float yy, float value);
void PerlinNoise(float**& heightMap, int width, int height, float scaleBias, int seed, int octaveCount, float persistance, float lacunarity);
void Falloff(float**& falloffMap, int width, int height, float mult);
float Evaluate(float value);