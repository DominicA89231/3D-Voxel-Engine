#pragma once
class Vector3f
{
public:
	float x, y, z;
	Vector3f(float _x, float _y, float _z);
	Vector3f();
	Vector3f normalize();
	Vector3f operator+(Vector3f other);
	Vector3f operator-(Vector3f other);
	Vector3f operator*(float other);
	float operator*(Vector3f other);
	Vector3f operator^(Vector3f other);
	Vector3f operator/(float other);
	float length();
};

