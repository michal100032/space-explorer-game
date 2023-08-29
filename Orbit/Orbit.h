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
	float m_meanAngular = 0.0f;

	// the body the spacecraft is orbiting
	CelestialBody* m_body = nullptr;

public:
	Orbit();
	Orbit(const Vector2f& position, const Vector2f& velocity);
	Orbit(CelestialBody* body, float sma, float ecc, float tilt, float trueAnomaly, float sam);

	void update(const Vector2f& position, const Vector2f& velocity);
	void updateWithinSOI(const Vector2f& position, const Vector2f& velocity);

	void progress(float dt);
	
	Vector2f getPosition() const;
	Vector2f getVelocity() const;

	float periapsis() const;
	float apoapsis() const;

	Vector3f eccVec() const;
	float eccentricity() const;
	float semiMajorAxis() const;
	float semiMinorAxis() const;
	float tilt() const;
	float trueAnomaly() const;
	float eccentricAnomaly() const;
	float meanAnomaly() const;
	float sam() const;

	float time() const;
	float period() const;

	CelestialBody* body() const;
	float distanceFromBody() const;

	static float meanFromEccentric(float ea, float ecc);
	static float eccentricFromTrue(float ta, float ecc);

	static float trueFromEccentric(float ea, float ecc);
	static float eccentricFromMean(float ma, float eccf);

	static float meanFromTrue(float ta, float ecc);
	static float trueFromMean(float ma, float ecc);

	static float meanFromEccentricHyp(float ea, float ecc);
	static float eccentricFromTrueHyp(float ta, float ecc);

	static float trueFromEccentricHyp(float ea, float ecc);
	static float eccentricFromMeanHyp(float ma, float eccf);

	static float meanFromTrueHyp(float ta, float ecc);
	static float trueFromMeanHyp(float ma, float ecc);


	bool isElliptical() const;
	bool isHyperbolic() const;

	friend class OrbitShape;
	friend class Simulation;
};
