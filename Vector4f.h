#pragma once
#include "Vector3f.h"
#include "Camera.h"

class Vector4f
{
public:
	// x, y, z are imaginary, a is real
	float x, y, z, a;
	Vector4f()
	{
		x = 0; y = 0; z = 0; a = 0;
	}
	Vector4f(float _x, float _y, float _z, float _a)
	{
		x = _x; y = _y; z = _z; a = _a;
	}
	Vector4f(Vector3f vector)
	{
		a = 0; x = vector.x; y = vector.y; z = vector.z;
	}
	void zero()
	{
		a = 0; x = 0; y = 0; z = 0;
	}
	Vector4f operator*(Vector4f other)
	{
		Vector4f new_vec;
		new_vec.a = a * other.a - x * other.x - y * other.y - z * other.z;
		new_vec.x = a * other.x + x * other.a + y * other.z - z * other.y;
		new_vec.y = a * other.y - x * other.z + y * other.a + z * other.x;
		new_vec.z = a * other.z + x * other.y - y * other.x + z * other.a;
		return new_vec;
	}
	static Vector3f rotatePoint(Vector3f line, Vector3f point, float angle)
	{
		// rotates point around line
		Vector4f q, g, p(point);
		line = line.normalize();
		q.a = cos(angle / 2)		 ; g.a = q.a;
		q.x = sin(angle / 2) * line.x; g.x = -q.x;
		q.y = sin(angle / 2) * line.y; g.y = -q.y;
		q.z = sin(angle / 2) * line.z; g.z = -q.z;
		p = q * p * g;

		return p.convertToVector3();
	}
	Vector3f convertToVector3()
	{
		return Vector3f(x, y, z);
	}
};