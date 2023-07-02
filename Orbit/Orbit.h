#pragma once

#include <SFML/Graphics.hpp>

#include "../Math/Vector3f.h"
#include "../Object/CelestialBody.h"

class Orbit {
private:
	// eccentricity
	Vector3f m_ecc;
	// semi-major axis
	float m_sma = 0.0f;
	
	// the tilt
	float m_tilt = 0.0f;
	
	// true anomaly
	float m_ta = 0.0f;

	// the body the spacecraft is orbiting
	CelestialBody* m_body = nullptr;
public:
	Orbit();
	Orbit(Vector2f position, Vector2f velocity);
	void update(Vector2f position, Vector2f velocity);

	float periapsis();
	float apoapsis();

	Vector3f eccVec();
	float eccentricity();
	float semiMajorAxis();
	float semiMinorAxis();
	float tilt();
	float trueAnomaly();
	float eccentricAnomaly();
	float meanAnomaly();

};