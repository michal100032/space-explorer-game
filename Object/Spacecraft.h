#pragma once
#include "Object.h"

#include "../Orbit/Orbit.h"
#include "../Object/OrbitRenderer.h"
#include "../Simulation/Simulation.h"

#include <SFML/Graphics.hpp>


class Spacecraft : public Object {
	sf::ConvexShape m_shape;
	Orbit m_orbit;

	Vector2f m_velocity;
	float m_angularSpeed = 0.0f;
	float m_encounterTime = 0.0f;
	bool m_encounterExpected = false;

	const float c_angularAcceleration = 1.5f;
	const float c_angularDecceleration = 0.9f;
	const float c_acceleration = 0.01f;

	sf::Text* m_stats[14];

	OrbitRenderer* m_orbRenderer = nullptr;

	Simulation::Results m_results;

	void initShape();
	void initStats();

	void updateStats();
	void updateOrbitStats();

	void accelerate();
	void updateRotation();
	void updatePosition();
	void displaySimulationResults();

	bool soiEncounterExpected();
	void makeEncounter();
public:
	Spacecraft(const std::string& name, Vector2f position, Vector2f velocity);
	Spacecraft(const std::string& name, const Orbit& orbit);


	void update() override;
	sf::Drawable* getDrawable() override;

	Orbit* getOrbit();

	Vector2f getVelocity() override;

	friend class Simulation;
};

