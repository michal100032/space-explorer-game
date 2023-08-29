#pragma once

#include "Object.h"
#include "../Orbit/Orbit.h"
#include "../Shapes/OrbitDrawable.h"

class OrbitRenderer : public Object {
private:
	Orbit* m_orbit = nullptr;
	OrbitDrawable m_drawable;

	sf::Color m_color;
	float m_outlineThickness = 3.0f;

	ShapeObject* m_indicators[3];
	Vector2f m_encounterPosition;

public:

	OrbitRenderer(Orbit* orbit);
	void refresh();
	void update() override;

	sf::Drawable* getDrawable() override;

	enum {
		IND_ENC = 0,
		IND_PER = 1,
		IND_APO = 2
	};
	void setEncInd(bool active);
	void setEncIndPosition(const Vector2f& position);


	~OrbitRenderer();
};