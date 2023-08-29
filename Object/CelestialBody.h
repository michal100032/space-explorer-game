#pragma once
#include <vector>

#include "Object.h"
#include "ShapeObject.h"

class CelestialBody : public Object {
private:
	sf::CircleShape m_shape;
	float m_mass = 0.0f;
	float m_radius = 0.0f;
	
	float m_angularSpeed = 0.0f;
	float m_orbitalTime = 0.0f;
	float m_orbitalRadius = -1.0f;
	float m_orbitalPeriod = -1.0f;
	float m_soi = 0.0f;

	float m_gp = 0.0f;

	CelestialBody* m_parent = nullptr;
	std::vector<CelestialBody*> m_children;

	static CelestialBody* root;

	ShapeObject* m_soiSprite = nullptr;
public:
	CelestialBody(const std::string& name, float mass, float radius, sf::Color color);

	void update() override;
	
	Vector2f getVelocity() override;
	float gp();

	void calculateSoi();
	void addChild(CelestialBody* child, float radius, float initialAngle);

	sf::Drawable* getDrawable() override;

	static CelestialBody* whoseSoi(Vector2f position);

	Vector2f gfs(Vector2f position);
	float soi();
	float mass();
	float radius();
	CelestialBody* parent();
	float orbitalRadius();
	float orbitalAngle();
	uint32_t colorInt();


	friend class Simulation;
};

