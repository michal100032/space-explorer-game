#pragma once
#include "Object.h"

class Spacecraft : public Object {
	sf::ConvexShape m_shape;
public:
	Spacecraft(const std::string& name, sf::Color color);
	void update() override;
	sf::Shape* getShape() override;
};

