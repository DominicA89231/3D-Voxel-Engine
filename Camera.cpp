#include "Camera.h"
#include "Vector4f.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265359

Camera::Camera()
{
	rotXY = 0; rotZ = 0;
	rot_speed = 15; move_speed = 100;
	position = Vector3f();
	center.setFillColor(sf::Color::Black);
	center.setRadius(2);
	x_axis.resize(2);
	x_axis.setPrimitiveType(sf::Lines);
	y_axis.resize(2);
	y_axis.setPrimitiveType(sf::Lines);
	z_axis.resize(2);
	z_axis.setPrimitiveType(sf::Lines);
}

void Camera::update(sf::Mouse mouse, sf::RenderWindow& window, float dt)
{
	Vector3f move_direction, rot_direction;

	sf::Vector2i mouse_position = mouse.getPosition(window);
	sf::Vector2f mouse_direction = sf::Vector2f(mouse_position.x - size.x / 2, mouse_position.y - size.y / 2);
	float length = sqrt(mouse_direction.x * mouse_direction.x + mouse_direction.y * mouse_direction.y);
	if (length > 0)
	{
		mouse_direction = mouse_direction / length;
	}
	else
	{
		mouse_direction = sf::Vector2f(0, 0);
	}

	rotXY += mouse_direction.x * rot_speed * dt;
	rotZ += mouse_direction.y * rot_speed * dt;
	if (rotZ < -PI / 2 + 0.001) rotZ = -PI / 2 + 0.001;
	else if (rotZ > PI / 2 - 0.001) rotZ = PI / 2 - 0.001;
	// Rotate around Z axis
	x_axis_vector = Vector4f::rotatePoint(Vector3f(0, 0, 1), Vector3f(1, 0, 0), rotXY);
	y_axis_vector = Vector4f::rotatePoint(Vector3f(0, 0, 1), Vector3f(0, 1, 0), rotXY);

	float dx = moving_states[0] - moving_states[1];
	float dy = moving_states[2] - moving_states[3];
	float dz = moving_states[4] - moving_states[5];
	move_direction = x_axis_vector * -dx + y_axis_vector * dy + Vector3f(0, 0, 1) * dz; // z_axis_vector * -dz
	position = move_direction.normalize() * move_speed * dt + position;


	// Rotate around Y axis
	x_axis_vector = Vector4f::rotatePoint(y_axis_vector, x_axis_vector, rotZ);
	// z_axis_vector = Vector4f::rotatePoint(y_axis_vector, Vector3f(0, 0, 1), rotZ);

	x_axis[0].color = sf::Color::Blue;
	x_axis[1].color = sf::Color::Blue;
	x_axis[0].position = project(x_axis_vector * 16);
	x_axis[1].position = project(16 * x_axis_vector.x + 1, 16 * x_axis_vector.y, 16 * x_axis_vector.z);

	y_axis[0].color = sf::Color::Green;
	y_axis[1].color = sf::Color::Green;
	y_axis[0].position = project(x_axis_vector * 16);
	y_axis[1].position = project(16 * x_axis_vector.x, 16 * x_axis_vector.y + 1, 16 * x_axis_vector.z);

	z_axis[0].color = sf::Color::Red;
	z_axis[1].color = sf::Color::Red;
	z_axis[0].position = project(x_axis_vector * 16);
	//z_axis[1].position = sf::Vector2f(size.x / 2, size.y / 2 - 30 * cos(rotZ));
	z_axis[1].position = project(16 * x_axis_vector.x, 16 * x_axis_vector.y, 16 * x_axis_vector.z + 1);
	
	mouse.setPosition(sf::Vector2i(size.x / 2, size.y / 2), window);
	center.setPosition(sf::Vector2f(size.x / 2 - 1, size.y / 2 - 1));
}

void Camera::setCenter(Vector3f _center)
{
	position = _center;
}

void Camera::setSize(sf::Vector2f _size)
{
	size = _size;
}

void Camera::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(center);
	target.draw(x_axis);
	target.draw(y_axis);
	target.draw(z_axis);
}

bool Camera::drawState(float dx, float dy, float dz)
{
	Vector3f target = Vector3f(dx, dy, dz).normalize();
	if (x_axis_vector * target < 0) return false;
	return true;
}

float arccos(float ratio) {
	if (ratio > 1) ratio = 1;
	if (ratio < -1) ratio = -1;
	return acos(ratio);
}

sf::Vector2f Camera::project(float dx, float dy, float dz)
{
	Vector3f test_point(dx, dy, dz), gradient;
	float angleX, angleY, perp_dis;
	float x_displacement, y_displacement;
	gradient = x_axis_vector * 2;
	perp_dis = (gradient * test_point - gradient * x_axis_vector) / 2;
	test_point = test_point * 1 / (1 + perp_dis);
	test_point = test_point - x_axis_vector;
	if (test_point.length() == 0)
	{
		angleX = 0;
		angleY = 0;
	}
	else
	{
		angleX = arccos((y_axis_vector * test_point) / test_point.length());
		angleY = arccos((Vector3f(0, 0, 1) * test_point) / test_point.length());
	}

	if (angleY > 3.14159265359 / 2)
	{
		x_displacement = test_point.length() * cos(angleX) * size.x / 2;
		y_displacement = test_point.length() * sin(angleX) * size.x / 2;
	}
	else
	{
		x_displacement = test_point.length() * cos(angleX) * size.x / 2;
		y_displacement = -test_point.length() * sin(angleX) * size.x / 2;
	}
	if (drawState(dx, dy, dz))
		return sf::Vector2f(x_displacement + size.x / 2, y_displacement + size.y / 2);
	else
	{
		if (x_displacement < -size.x / 2 || x_displacement > size.x / 2 || y_displacement < -size.y / 2 || y_displacement > size.y / 2)
			return sf::Vector2f(-x_displacement + size.x / 2, -y_displacement + size.y / 2);
		else
		{
			float ratio1 = std::abs(size.x / (2 * x_displacement));
			float ratio2 = std::abs(size.y / (2 * y_displacement));
			if (ratio1 > ratio2)
				return sf::Vector2f(-x_displacement * ratio1 + size.x / 2, -y_displacement * ratio1 + size.y / 2);
			else
				return sf::Vector2f(-x_displacement * ratio2 + size.x / 2, -y_displacement * ratio2 + size.y / 2);
		}
	}
}

sf::Vector2f Camera::project(Vector3f vector)
{
	float dx = vector.x;
	float dy = vector.y;
	float dz = vector.z;
	Vector3f test_point(dx, dy, dz), gradient;
	float angleX, angleY, perp_dis;
	float x_displacement, y_displacement;
	gradient = x_axis_vector * 2;
	perp_dis = (gradient * test_point - gradient * x_axis_vector) / 2;
	test_point = test_point * 1 / (1 + perp_dis);
	test_point = test_point - x_axis_vector;
	if (test_point.length() == 0)
	{
		angleX = 0;
		angleY = 0;
	}
	else
	{
		angleX = arccos((y_axis_vector * test_point) / test_point.length());
		angleY = arccos((Vector3f(0, 0, 1) * test_point) / test_point.length());
	}

	if (angleY > 3.14159265359 / 2)
	{
		x_displacement = test_point.length() * cos(angleX) * size.x / 2 + size.x / 2;
		y_displacement = test_point.length() * sin(angleX) * size.x / 2 + size.y / 2;
	}
	else
	{
		x_displacement = test_point.length() * cos(angleX) * size.x / 2 + size.x / 2;
		y_displacement = -test_point.length() * sin(angleX) * size.x / 2 + size.y / 2;
	}
	if (drawState(dx, dy, dz))
		return sf::Vector2f(x_displacement, y_displacement);
	else
		return sf::Vector2f(-x_displacement, -y_displacement);
}