#pragma once

#include "../Object/Object.h"
#include "Orbit.h"

class OrbitRenderer : public Object {
private:
	Orbit* m_orbit = nullptr;
	sf::Shape* m_shape = nullptr;

	sf::Color m_color;
	float m_outlineThickness = 3.0f;
public:
	OrbitRenderer(Orbit* orbit);
	void refresh();

	sf::Shape* getShape() override;

	~OrbitRenderer();
};

