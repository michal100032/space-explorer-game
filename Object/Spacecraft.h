#pragma once
#include "Object.h"
#include "../Orbit/Orbit.h"

#include <SFML/Graphics.hpp>

class Spacecraft : public Object {
	sf::ConvexShape m_shape;
	Orbit m_orbit;

	Vector2f m_velocity;
	float m_angularSpeed = 0.0f;

	const float c_angularAcceleration = 1.5f;
	const float c_angularDecceleration = 0.99f;

	sf::Text* m_stats[9];

public:
	Spacecraft(Vector2f position, Vector2f velocity);
	void update() override;
	sf::Shape* getShape() override;

	Orbit* getOrbit();

	//void setVelocity() override;
	Vector2f getVelocity() override;
};

