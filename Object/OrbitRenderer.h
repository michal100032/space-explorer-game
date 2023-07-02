#pragma once

#include "Object.h"
#include "../Orbit/Orbit.h"

class OrbitRenderer : public Object {
private:
	Orbit* m_orbit = nullptr;
	sf::Shape* m_shape = nullptr;

	sf::Color m_color;
	float m_outlineThickness = 3.0f;
public:
	OrbitRenderer();
	void refresh();

	void setOrbit(Orbit* orbit);

	sf::Shape* getShape() override;

	~OrbitRenderer();
};

