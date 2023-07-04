#include "Orbit.h"

#include <iostream>

#include "../constants.h"

Orbit::Orbit()
	: m_body(nullptr), m_ecc(), m_sma(0.0f), m_tilt(0.0f) {}

Orbit::Orbit(const Vector2f& position, const Vector2f& velocity) {
	update(position, velocity);
}

float Orbit::meanFromEccentric(float ea, float ecc) {
	return ea - ecc * sinf(ea);
}

float Orbit::eccentricFromTrue(float ta, float ecc) {
	return 2 * atanf(sqrtf((1 - ecc) / (1 + ecc)) * tanf(ta / 2));
}

float Orbit::trueFromEccentric(float ea, float ecc) {
	return 2 * atanf(sqrtf((1 + ecc) / (1 - ecc)) * tanf(ea / 2));
}

float Orbit::eccentricFromMean(float ma, float eccf) {

	const int maxIterations = 20;

	double appx = consts::DPI / 2 * (ma > 0 ? 1 : -1);
	double ecc = eccf;
	for (int i = 0; i < maxIterations; i++) {
		appx = appx - (appx - ecc * sinf(appx) - ma) / (1 - ecc * cosf(appx));
	}
	return (float)appx;
}

float Orbit::meanFromTrue(float ta, float ecc) {
	float eccentric = eccentricFromTrue(ta, ecc);
	return meanFromEccentric(eccentric, ecc);
}

float Orbit::trueFromMean(float ma, float ecc) {	
	float eccentric = eccentricFromMean(ma, ecc);
	return trueFromEccentric(eccentric, ecc);
}

void Orbit::update(const Vector2f& position, const Vector2f& velocity) {
	m_body = CelestialBody::whoseSoi(position);

	m_sam = Vector3f::cross(position, velocity);
	m_ecc = Vector3f::cross((Vector3f)velocity, m_sam) / m_body->gp() - position.normalized();
	m_tilt = atan2f(m_ecc.y, m_ecc.x);

	m_sma = 1.0f / (2.0f / position.magnitude() - velocity.sqrMagnitude() / m_body->gp());

	m_ta = Vector2f::angle(position, m_ecc.sf2());
	if (m_ta > consts::PI) {
		m_ta -= consts::PI;
	}
	
	m_period = consts::DPI * sqrtf(m_sma * m_sma * m_sma / m_body->gp());
	m_ma = meanFromTrue(m_ta, m_ecc.magnitude());
	m_time = m_ma / consts::DPI * m_period;
}

void Orbit::accelerate(const Vector2f& acc) {
	Vector2f vel = getVelocity() + acc;
	update(getPosition(), vel);
}

void Orbit::progress(float dt) {
	m_time += dt;
	if (m_time > m_period) {
		m_time -= m_period;
	}
	m_ma = m_time * consts::DPI / m_period;

	if (m_ma > consts::PI) {
		m_ma -= consts::DPI;
	}

	m_ea = eccentricFromMean(m_ma, m_ecc.magnitude());
	m_ta = trueFromEccentric(m_ea, m_ecc.magnitude());
}

Vector2f Orbit::getPosition() {
	float r = m_sam.sqrMagnitude() / m_body->gp() / (1.0f + m_ecc.magnitude() * cosf(m_ta));
	float ang = consts::DPI - m_ta + m_tilt;
	return Vector2f(
		r * cosf(ang),
		r * sinf(ang)
	) + m_body->getPosition();
}

Vector2f Orbit::getVelocity() {
	float r = m_sam.sqrMagnitude() / m_body->gp() / (1.0f + m_ecc.magnitude() * cosf(m_ta));
	float speed = sqrtf(m_body->gp() * (2.0f / r - 1.0f / m_sma));

	float sinVr = m_sam.magnitude() / speed / r;
	float vr = asinf(sinVr);

	float angle = (m_ta > 0 ? vr : (consts::PI - vr)) - m_tilt + m_ta + consts::PI / 2;

	return Vector2f(
		speed * sinf(angle),
		speed * cosf(angle)
	);
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
	return m_ta;
}

float Orbit::eccentricAnomaly() {
	return m_ea;
}

float Orbit::meanAnomaly() {
	return m_ma;
}

float Orbit::time() {
	return m_time;
}

float Orbit::periapsis() {
	return m_sma * (1 - m_ecc.magnitude());
}

float Orbit::apoapsis() {
	return m_sma * (1 + m_ecc.magnitude());;
}
