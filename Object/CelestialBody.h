#pragma once
#include <vector>

#include "Object.h"

class CelestialBody : public Object {
private:
	sf::CircleShape m_shape;
	float m_mass = 0.0f;
	float m_radius = 0.0f;
	
	float m_orbitalTime = 0.0f;
	float m_orbitalRadius = -1.0f;
	float m_orbitalPeriod = -1.0f;
	float m_soi = 0.0f;

	float m_gp = 0.0f;

	CelestialBody* m_parent = nullptr;
	std::vector<CelestialBody*> m_children;

	static CelestialBody* root;
public:
	CelestialBody(const std::string& name, float mass, float radius, sf::Color color);

	void update() override;
	
	Vector2f getVelocity() override;
	float gp();

	void calculateSoi();
	void addChild(CelestialBody* child, float radius);

	sf::Shape* getShape() override;

	static CelestialBody* whoseSoi(Vector2f position);
};

