#include "CustomMath.h"
#include <iostream>

#pragma region Vec2
// ** CONTAINS ALL FUNCTIONS RELATED TO VEC2 **

// Operator overloads
Vec2 operator/(Vec2 vec, float divide)
{
	return Vec2(vec.x / divide, vec.y / divide);
}
Vec2 operator/=(Vec2& vec, float divide)
{
	vec.x = vec.x / divide;
	vec.y = vec.y / divide;
	return vec;
}
Vec2 operator*(Vec2 vec, float mult)
{
	return Vec2(vec.x * mult, vec.y * mult);
}
Vec2 operator*=(Vec2& vec, float mult)
{
	vec.x = vec.x * mult;
	vec.y = vec.y * mult;
	return vec;
}
Vec2 operator+(Vec2 vec, Vec2 add)
{
	return Vec2(vec.x + add.x, vec.y + add.y);
}
Vec2 operator+=(Vec2& vec, Vec2 add)
{
	vec.x = vec.x + add.x;
	vec.y = vec.y + add.y;
	return vec;
}
Vec2 operator-(Vec2 vec, Vec2 subtract)
{
	return Vec2(vec.x - subtract.x, vec.y - subtract.y);
}
Vec2 operator-=(Vec2& vec, Vec2 subtract)
{
	vec.x = vec.x - subtract.x;
	vec.y = vec.y - subtract.y;
	return vec;
}

// Functions and constructors
Vec2::Vec2()
{
	x = 0;
	y = 0;
}
Vec2::Vec2(float a, float b)
{
	x = a;
	y = b;
}
float Vec2::Dot(Vec2 vec)
{
	return (x * vec.x + y * vec.y);
}
Vec2 Vec2::Cross(Vec2 vec)
{
	return Vec2(y * vec.x - x * vec.y, x * vec.y - y * vec.x);
}
float Vec2::Magnitude()
{
	float sum = 0;
	if (x != 0)
		sum += x * x;
	if (y != 0)
		sum += y * y;
	
	if (sum != 0)
		return sqrtf(sum);

	return 0;
}
float Vec2::MagnitudeSqr()
{
	return (x * x + y * y);
}
void Vec2::Normalise()
{
	float mag = Magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
	}
}
Vec2 Vec2::GetNormalised()
{
	Vec2 result;
	float mag = Magnitude();

	if (mag != 0)
	{
		result.x = x / mag;
		result.y = y / mag;
	
		return result;
	}

	result.x = 0;
	result.y = 0;

	return result;
}
float Vec2::Distance(Vec2 target)
{
	float diffX = x - target.x;
	float diffY = y - target.y;

	return sqrtf(diffX * diffX + diffY * diffY);
}

#pragma endregion

#pragma region Vec3
// ** CONTAINS ALL FUNCTIONS RELATED TO VEC3 **

// Operator overloads
Vec3 operator/(Vec3 vec, float divide)
{
	vec.x /= divide;
	vec.y /= divide;
	vec.z /= divide;
	return vec;
}
Vec3 operator/=(Vec3& vec, float divide)
{
	vec.x /= divide;
	vec.y /= divide;
	vec.z /= divide;
	return vec;
}
Vec3 operator*(Vec3 vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	vec.z *= mult;
	return vec;
}
Vec3 operator*=(Vec3& vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	vec.z *= mult;
	return vec;
}
Vec3 operator+(Vec3 vec, Vec3 add)
{
	vec.x += add.x;
	vec.y += add.y;
	vec.z += add.z;
	return vec;
}
Vec3 operator+=(Vec3& vec, Vec3 add)
{
	vec.x += add.x;
	vec.y += add.y;
	vec.z += add.z;
	return vec;
}
Vec3 operator-(Vec3 vec, Vec3 subtract)
{
	vec.x -= subtract.x;
	vec.y -= subtract.y;
	vec.z -= subtract.z;
	return vec;
}
Vec3 operator-=(Vec3& vec, Vec3 subtract)
{
	vec.x -= subtract.x;
	vec.y -= subtract.y;
	vec.z -= subtract.z;
	return vec;
}

// Functions and constructors
Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}
Vec3::Vec3(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}
float Vec3::Dot(Vec3 vec)
{
	return (x * vec.x + y * vec.y + z * vec.z);
}
float Vec3::Magnitude()
{
	float sum = 0;
	if (x != 0)
		sum += x * x;
	if (y != 0)
		sum += y * y;
	if (z != 0)
		sum += z * z;

	if (sum != 0)
		return sqrtf(sum);

	return 0;
}
float Vec3::MagnitudeSqr()
{
	return (x * x + y * y + z * z);
}
void Vec3::Normalise()
{
	float mag = Magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
}
Vec3 Vec3::GetNormalised()
{
	Vec3 result;
	float mag = Magnitude();

	if (mag != 0)
	{
		result.x = x / mag;
		result.y = y / mag;
		result.z = z / mag;

		return result;
	}

	result.x = 0;
	result.y = 0;
	result.z = 0;

	return result;
}
float Vec3::Distance(Vec3 target)
{
	float diffX = x - target.x;
	float diffY = y - target.y;
	float diffZ = z - target.z;

	return sqrtf(diffX * diffX + diffY * diffY + diffZ * diffZ);
}

#pragma endregion

#pragma region Vec4
// ** CONTAINS ALL FUNCTIONS RELATED TO VEC4 **

// Operator overloads
Vec4 operator/(Vec4 vec, float divide)
{
	vec.x /= divide;
	vec.y /= divide;
	vec.z /= divide;
	vec.w /= divide;
	return vec;
}
Vec4 operator/=(Vec4& vec, float divide)
{
	vec.x /= divide;
	vec.y /= divide;
	vec.z /= divide;
	vec.w /= divide;
	return vec;
}
Vec4 operator*(Vec4 vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	vec.z *= mult;
	vec.w *= mult;
	return vec;
}
Vec4 operator*=(Vec4& vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	vec.z *= mult;
	vec.w *= mult;
	return vec;
}
Vec4 operator+(Vec4 vec, Vec4 add)
{
	vec.x += add.x;
	vec.y += add.y;
	vec.z += add.z;
	vec.w += add.w;
	return vec;
}
Vec4 operator+=(Vec4& vec, Vec4 add)
{
	vec.x += add.x;
	vec.y += add.y;
	vec.z += add.z;
	vec.w += add.w;
	return vec;
}
Vec4 operator-(Vec4 vec, Vec4 subtract)
{
	vec.x -= subtract.x;
	vec.y -= subtract.y;
	vec.z -= subtract.z;
	vec.w -= subtract.w;
	return vec;
}
Vec4 operator-=(Vec4& vec, Vec4 subtract)
{
	vec.x -= subtract.x;
	vec.y -= subtract.y;
	vec.z -= subtract.z;
	vec.w -= subtract.w;
	return vec;
}

// Functions and constructors
Vec4::Vec4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}
Vec4::Vec4(float a, float b, float c, float d)
{
	x = a;
	y = b;
	z = c;
	w = d;
}
Vec4::Vec4(Vec2 a, Vec2 b)
{
	x = a.x;
	y = a.y;
	z = b.x;
	w = b.y;
}
float Vec4::Dot(Vec4 vec)
{
	return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
}
float Vec4::Magnitude()
{
	float sum = 0;
	if (x != 0)
		sum += x * x;
	if (y != 0)
		sum += y * y;
	if (z != 0)
		sum += z * z;
	if (w != 0)
		sum += w * w;

	if (sum != 0)
		return sqrtf(sum);

	return 0;
}
float Vec4::MagnitudeSqr()
{
	return (x * x + y * y + z * z + w * w);
}
void Vec4::Normalise()
{
	float mag = Magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
}
Vec4 Vec4::GetNormalised()
{
	Vec4 result;
	float mag = Magnitude();

	if (mag != 0)
	{
		result.x = x / mag;
		result.y = y / mag;
		result.z = z / mag;
		result.w = w / mag;

		return result;
	}

	result.x = 0;
	result.y = 0;
	result.z = 0;
	result.w = 0;

	return result;
}
float Vec4::Distance(Vec4 target)
{
	float diffX = x - target.x;
	float diffY = y - target.y;
	float diffZ = z - target.z;
	float diffW = w - target.w;

	return sqrtf(diffX * diffX + diffY * diffY + diffZ * diffZ + diffW * diffW);
}

#pragma endregion

float Max(float a, float b)
{
	if (a >= b)
		return a;

	return b;
}

float Min(float a, float b)
{
	if (a <= b)
		return a;

	return b;
}

float Abs(float value)
{
	if (value < 0)
		return value * -1;

	return value;
}

float Clamp(float value, float lower, float upper)
{
	return Max(lower, Min(value, upper));
}

float RandomFloat(float min, float max)
{
	float range = max - min;
	float value = (float)rand() / (float)RAND_MAX;
	value *= range;

	return value + min;
}

float InverseLerp(float xx, float yy, float value)
{
	float a = value - xx;
	float b = yy - xx;
	float c = a / b;
	return c;
}

void PerlinNoise(float**&heightMap, int width, int height, float scaleBias, int seed, int octaveCount, float persistance, float lacunarity)
{
	FastNoise fNoise;
	fNoise.SetNoiseType(FastNoise::NoiseType::SimplexFractal);
	fNoise.SetSeed(seed);

	// Ensure octave count does not exceed 8...
	if (octaveCount > 8)
		octaveCount = octaveCount % 8;
	// ...or deceed 1
	else if (octaveCount < 1)
		octaveCount = 1;

	// Set min and max heights to max and min float values
	float minNoiseHeight = FLT_MAX;
	float maxNoiseHeight = -FLT_MAX;

	float averageHeight = 0;

	// And so the 
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			float amplitude = 1;
			float frequency = 1;
			float noiseHeight = 0;

			for (int o = 0; o < octaveCount; o++)
			{
				float sampleX = x / scaleBias * frequency;
				float sampleY = y / scaleBias * frequency;
				float perlinValue = fNoise.GetNoise(sampleX, sampleY) * 2 - 1;
				noiseHeight += perlinValue * amplitude;

				amplitude *= persistance;
				frequency *= lacunarity;
			}

			// Set min and max noise height values
			if (noiseHeight > maxNoiseHeight)
				maxNoiseHeight = noiseHeight;
			else if (noiseHeight < minNoiseHeight)
				minNoiseHeight = noiseHeight;

			// Assign noise height to map
			heightMap[x][y] = noiseHeight;
		}
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// Basically a normalise function. Returns a value between 0 and 1.
			heightMap[x][y] = InverseLerp(minNoiseHeight, maxNoiseHeight, heightMap[x][y]);

			averageHeight += heightMap[x][y];
		}
	}

	averageHeight /= (width * height);
}

void Falloff(float**& falloffMap, int width, int height, float mult)
{
	float averageHeight = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// Get x and y values between -1 and 1
			float a = (float)x / (float)width * 2 - 1;
			float b = (float)y / (float)height * 2 - 1;

			// Get the value that is closest to -1 or 1 and assign it to map
			float value = Max(Abs(a), Abs(b)) / mult;
			//value = Evaluate(value);

			falloffMap[x][y] = value;

			averageHeight += value;
		}
	}

	averageHeight /= (width * height);
}

float Evaluate(float value)
{
	float a = 3;
	float b = 2.2f;

	return pow(value, a) / pow(value, a) + pow(b - b * value, a);
}