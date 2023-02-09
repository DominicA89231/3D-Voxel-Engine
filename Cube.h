#pragma once
#include "Vector3f.h"
#include "Camera.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
class Cube : public sf::Drawable
{
	// top or bottom
	sf::VertexArray side1;
	// west or east
	sf::VertexArray side2;
	// north or south
	sf::VertexArray side3;
public:
	Cube(float _side_length, Vector3f _position, sf::Texture* _side);
	void update(Camera camera);
	sf::Texture* side;
	Vector3f position;
	float side_length;
	// +x, -x, +y, -y, +z, -z
	bool adjacent[6] = { false };
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
};

