#pragma once
#include "Vector3f.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class Camera : public sf::Drawable
{
public:
	float rotXY, rotZ;
	Vector3f position;
	sf::Vector2f size;
	sf::CircleShape center;
	sf::VertexArray x_axis;
	sf::VertexArray y_axis;
	sf::VertexArray z_axis;
	Vector3f z_axis_vector, x_axis_vector, y_axis_vector;
	float rot_speed;
	float move_speed; 
	// camera moving states
	bool moving_states[6] = {false};
	Camera();
	void update(sf::Mouse mouse, sf::RenderWindow& window, float dt);
	void setCenter(Vector3f _center);
	void setSize(sf::Vector2f _size);
	bool drawState(float dx, float dy, float dz);
	bool testQuadrant(char axis);
	sf::Vector2f project(float dx, float dy, float dz);
	sf::Vector2f project(Vector3f vector);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
};

