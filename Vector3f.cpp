#include "Vector3f.h"
#include <cmath>

Vector3f::Vector3f(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

Vector3f::Vector3f()
{
	x = 0; y = 0; z = 0;
}

Vector3f Vector3f::normalize()
{
	float d = sqrt(x * x + y * y + z * z);
	if (d == 0)
		return Vector3f();
	return Vector3f(x, y, z) / d;
}

Vector3f Vector3f::operator+(Vector3f other) 
{
	return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator-(Vector3f other)
{
	return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f Vector3f::operator*(float other)
{
	return Vector3f(x * other, y * other, z * other);
}

Vector3f Vector3f::operator^(Vector3f other)
{
	return Vector3f(y * other.z - z * other.y, - x * other.z + z * other.x, x * other.y - y * other.x);
}

float Vector3f::operator*(Vector3f other)
{
	return x * other.x + y * other.y + z * other.z;
}
Vector3f Vector3f::operator/(float other)
{
	return Vector3f(x / other, y / other, z / other);
}

float Vector3f::length()
{
	return sqrt(x * x + y * y + z * z);
}