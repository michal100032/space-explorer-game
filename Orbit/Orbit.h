#pragma once

#include <SFML/Graphics.hpp>

#include "../Math/Vector3f.h"
#include "../Object/CelestialBody.h"

class Orbit {
private:

	// eccentricity
	Vector3f m_ecc;
	// specific angular momentum
	Vector3f m_sam;
	// semi-major axis
	float m_sma = 0.0f;
	
	// the tilt
	float m_tilt = 0.0f;
	
	float m_ta = 0.0f, m_ea = 0.0f, m_ma = 0.0f;

	float m_time = 0.0f;
	float m_period = 0.0f;

	// the body the spacecraft is orbiting
	CelestialBody* m_body = nullptr;

	static float meanFromEccentric(float ea, float ecc);
	static float eccentricFromTrue(float ta, float ecc);

	static float trueFromEccentric(float ea, float ecc);
	static float eccentricFromMean(float ma, float eccf);

	static float meanFromTrue(float ta, float ecc);
	static float trueFromMean(float ma, float ecc);

public:
	Orbit();
	Orbit(const Vector2f& position, const Vector2f& velocity);
	void update(const Vector2f& position, const Vector2f& velocity);
	void accelerate(const Vector2f& acc);

	void progress(float dt);
	
	Vector2f getPosition();
	Vector2f getVelocity();

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

	float time();

};