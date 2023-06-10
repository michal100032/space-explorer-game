#pragma once
#include "Object.h"
#include "../Orbit/Orbit.h"
#include "../Orbit/OrbitRenderer.h"

class Spacecraft : public Object {
	sf::ConvexShape m_shape;
	Orbit m_orbit;
	OrbitRenderer* m_orbitRenderer = nullptr;

	Vector2f m_velocity;

public:
	Spacecraft(const std::string& name, sf::Color color);
	void update() override;
	sf::Shape* getShape() override;


	//void setVelocity() override;
	Vector2f getVelocity() override;
};

