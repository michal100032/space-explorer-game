#include "Orbit.h"

#include <iostream>

Orbit::Orbit()
	: m_body(nullptr), m_ecc(), m_sma(0.0f), m_tilt(0.0f) {}

Orbit::Orbit(Vector2f position, Vector2f velocity) {
	update(position, velocity);
}

void Orbit::update(Vector2f position, Vector2f velocity) {
	m_body = CelestialBody::whoseSoi(position);

	Vector3f SAM = Vector3f::cross(position, velocity);
	m_ecc = Vector3f::cross((Vector3f)velocity, SAM) / m_body->gp() - position.normalized();
	m_tilt = atan2f(m_ecc.y, m_ecc.x);

	m_sma = 1.0f / (2.0f / position.magnitude() - velocity.sqrMagnitude() / m_body->gp());
}

Vector3f Orbit::eccVec() {
	return m_ecc;
}

float Orbit::eccentricity() {
	return m_ecc.magnitude();
}

float Orbit::semiMajorAxis() {
	return m_sma;
} 

float Orbit::semiMinorAxis() {
	return m_sma * sqrtf(1 - m_ecc.sqrMagnitude());
}

float Orbit::tilt() {
	return m_tilt;
}

float Orbit::trueAnomaly() {
	return 0.0f;
}

float Orbit::eccentricAnomaly() {
	return 0.0f;
}

float Orbit::meanAnomaly() {
	return 0.0f;
}

float Orbit::periapsis() {
	return m_sma * (1 - m_ecc.magnitude());
}

float Orbit::apoapsis() {
	return m_sma * (1 + m_ecc.magnitude());;
}
