#include "Cube.h"
#include <cmath>
#include <iostream>
#include "Vector4f.h"
#define PI 3.141592653589

Cube::Cube(float _side_length, Vector3f _position, sf::Texture* _side)
{
	side_length = _side_length;
	position = _position;

	// top or bottom
	side1.resize(4);
	side1.setPrimitiveType(sf::Quads);

	// west or east
	side2.resize(4);
	side2.setPrimitiveType(sf::Quads);

	// north or south
	side3.resize(4);
	side3.setPrimitiveType(sf::Quads);

	for (int i = 0; i < 4; i++)
		side1[i].color = sf::Color::Red;
	for (int i = 0; i < 4; i++)
		side2[i].color = sf::Color::Green;
	for (int i = 0; i < 4; i++)
		side3[i].color = sf::Color::Blue;

	side1[0].texCoords = sf::Vector2f(0.f , 0.f);
	side1[1].texCoords = sf::Vector2f(16.f, 0.f);
	side1[2].texCoords = sf::Vector2f(16.f, 16.f);
	side1[3].texCoords = sf::Vector2f(0.f , 16.f);

	side2[0].texCoords = sf::Vector2f(0.f, 0.f);
	side2[1].texCoords = sf::Vector2f(16.f, 0.f);
	side2[2].texCoords = sf::Vector2f(16.f, 16.f);
	side2[3].texCoords = sf::Vector2f(0.f, 16.f);

	side3[0].texCoords = sf::Vector2f(0.f, 0.f);
	side3[1].texCoords = sf::Vector2f(16.f, 0.f);
	side3[2].texCoords = sf::Vector2f(16.f, 16.f);
	side3[3].texCoords = sf::Vector2f(0.f, 16.f);

	side = _side;
}

void Cube::update(Camera camera)
{
	float x0, y0, z0, x1, y1, z1;
	x0 = position.x - camera.position.x; x1 = x0 + side_length;
	y0 = position.y - camera.position.y; y1 = y0 + side_length;
	z0 = position.z - camera.position.z; z1 = z0 + side_length;

	side1[0].position = sf::Vector2f(0, 0);
	side1[1].position = sf::Vector2f(0, 0);
	side1[2].position = sf::Vector2f(0, 0);
	side1[3].position = sf::Vector2f(0, 0);
	side2[0].position = sf::Vector2f(0, 0);
	side2[1].position = sf::Vector2f(0, 0);
	side2[2].position = sf::Vector2f(0, 0);
	side2[3].position = sf::Vector2f(0, 0);
	side3[0].position = sf::Vector2f(0, 0);
	side3[1].position = sf::Vector2f(0, 0);
	side3[2].position = sf::Vector2f(0, 0);
	side3[3].position = sf::Vector2f(0, 0);

	if (z0 > 0)
	{
		// bottom side
		if (!adjacent[5] && (camera.drawState(x0, y0, z0) || camera.drawState(x0, y1, z0) || camera.drawState(x1, y0, z0) || camera.drawState(x1, y1, z0)))
		{
			side1[0].position = camera.project(x0, y0, z0);
			side1[1].position = camera.project(x1, y0, z0);
			side1[2].position = camera.project(x1, y1, z0);
			side1[3].position = camera.project(x0, y1, z0);

			sf::Vector2f displacement = (camera.project(x1, y1, z0) - camera.project(x0, y0, z0));
			float dis_ratio = std::sqrt(displacement.x * displacement.x + displacement.y * displacement.y) / (50 * sqrt(2));

			side1[0].texCoords = sf::Vector2f(0.f, 0.f);
			side1[1].texCoords = sf::Vector2f(16.f * dis_ratio, 0.f);
			side1[2].texCoords = sf::Vector2f(16.f * dis_ratio, 16.f * dis_ratio);
			side1[3].texCoords = sf::Vector2f(0.f, 16.f * dis_ratio);
		}
	}

	else if (z1 < 0)
	{
		// top side
		if (!adjacent[4] && (camera.drawState(x0, y0, z1) || camera.drawState(x0, y1, z1) || camera.drawState(x1, y0, z1) || camera.drawState(x1, y1, z1)))
		{
			side1[0].position = camera.project(x0, y0, z1);
			side1[1].position = camera.project(x1, y0, z1);
			side1[2].position = camera.project(x1, y1, z1);
			side1[3].position = camera.project(x0, y1, z1);
		}
	}

	if (y0 > 0)
	{
		// west side
		if (!adjacent[2] && (camera.drawState(x0, y0, z0) || camera.drawState(x0, y0, z1) || camera.drawState(x1, y0, z1) || camera.drawState(x1, y0, z0)))
		{
			side2[0].position = camera.project(x0, y0, z1);
			side2[1].position = camera.project(x1, y0, z1);
			side2[2].position = camera.project(x1, y0, z0);
			side2[3].position = camera.project(x0, y0, z0);
		}
	}

	else if (y1 < 0)
	{
		// east side
		if (!adjacent[3] && (camera.drawState(x0, y1, z0) || camera.drawState(x0, y1, z1) || camera.drawState(x1, y1, z1) || camera.drawState(x1, y1, z0)))
		{
			side2[0].position = camera.project(x0, y1, z1);
			side2[1].position = camera.project(x1, y1, z1);
			side2[2].position = camera.project(x1, y1, z0);
			side2[3].position = camera.project(x0, y1, z0);
		}
	}

	if (x0 > 0)
	{
		// south side
		if (!adjacent[0] && (camera.drawState(x0, y0, z0) || camera.drawState(x0, y1, z1) || camera.drawState(x0, y0, z1) || camera.drawState(x0, y1, z0)))
		{
			side3[0].position = camera.project(x0, y1, z1);
			side3[1].position = camera.project(x0, y0, z1);
			side3[2].position = camera.project(x0, y0, z0);
			side3[3].position = camera.project(x0, y1, z0);
		}
	}

	else if (x1 < 0)
	{
		// north side
		if (!adjacent[1] && (camera.drawState(x1, y0, z0) || camera.drawState(x1, y1, z1) || camera.drawState(x1, y0, z1) || camera.drawState(x1, y1, z0)))
		{
			side3[0].position = camera.project(x1, y1, z1);
			side3[1].position = camera.project(x1, y0, z1);
			side3[2].position = camera.project(x1, y0, z0);
			side3[3].position = camera.project(x1, y1, z0);
		}
	}
}

void Cube::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(side1);
	target.draw(side2);
	target.draw(side3);
}