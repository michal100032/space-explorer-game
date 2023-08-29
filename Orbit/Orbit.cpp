#include "Orbit.h"

#include <iostream>

#include "../constants.h"

Orbit::Orbit()
	: m_body(nullptr), m_ecc(), m_sma(0.0f), m_tilt(0.0f) {}

Orbit::Orbit(const Vector2f& position, const Vector2f& velocity) {
	update(position, velocity);
}

Orbit::Orbit(CelestialBody* body, float sma, float ecc, float tilt, float trueAnomaly, float sam)
	: m_body(body), m_sma(sma), m_ecc(cosf(tilt) * ecc, sinf(tilt) * ecc, 0.0f), m_ta(trueAnomaly), m_sam(0.0f, 0.0f, sam) {

	if (isElliptical()) {
		m_ma = meanFromTrue(m_ta, ecc);
		m_meanAngular = sqrtf(m_body->gp() / (m_sma * m_sma * m_sma));
		m_period = consts::DPI / m_meanAngular;
	}
	else {
		m_ma = meanFromTrueHyp(m_ta, ecc);
		m_meanAngular = sqrtf(-m_body->gp() / (m_sma * m_sma * m_sma));
	}

	m_time = m_ma / (m_sam.z > 0.0f ? -m_meanAngular : m_meanAngular);
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

float Orbit::eccentricFromMean(float ma, float ecc) {

	const int iterations = 20;

	float appx = ma;
	for (int i = 0; i < iterations; i++) {
		appx = appx - (appx - ecc * sinf(appx) - ma) / (1 - ecc * cosf(appx));
	}
	return appx;
}

float Orbit::meanFromTrue(float ta, float ecc) {
	float eccentric = eccentricFromTrue(ta, ecc);
	return meanFromEccentric(eccentric, ecc);
}

float Orbit::trueFromMean(float ma, float ecc) {	
	float eccentric = eccentricFromMean(ma, ecc);
	return trueFromEccentric(eccentric, ecc);
}


float Orbit::meanFromEccentricHyp(float ea, float ecc) {
	return ecc * sinhf(ea) - ea;
}

float Orbit::eccentricFromTrueHyp(float ta, float ecc) {
	return 2 * atanhf(sqrtf((ecc - 1) / (ecc + 1)) * tanf(ta / 2));
}

float Orbit::trueFromEccentricHyp(float ea, float ecc) {
	return 2 * atanf(sqrtf((ecc + 1) / (ecc - 1)) * tanhf(ea / 2));
}

float Orbit::eccentricFromMeanHyp(float ma, float ecc) {

	const int iterations = 20;
	
	float appx = ma;
	for (int i = 0; i < iterations; i++) {
		appx = appx + (ma - ecc * sinhf(appx) + appx) / (ecc * coshf(appx) - 1);
	}
	return appx;
}

float Orbit::meanFromTrueHyp(float ta, float ecc) {
	float eccentric = eccentricFromTrueHyp(ta, ecc);
	return meanFromEccentricHyp(eccentric, ecc);
}

float Orbit::trueFromMeanHyp(float ma, float ecc) {
	float eccentric = eccentricFromMeanHyp(ma, ecc);
	return trueFromEccentricHyp(eccentric, ecc);
}

void Orbit::update(const Vector2f& position, const Vector2f& velocity) {
	m_body = CelestialBody::whoseSoi(position);

	Vector2f rv = velocity - m_body->getVelocity();
	Vector2f displ = position - m_body->getPosition();

	m_sam = Vector3f::cross(displ, rv);
	m_ecc = Vector3f::cross((Vector3f)rv, m_sam) / m_body->gp() - displ.normalized();
	m_tilt = atan2f(m_ecc.y, m_ecc.x);

	m_sma = 1.0f / (2.0f / displ.magnitude() - rv.sqrMagnitude() / m_body->gp());

	m_ta = Vector2f::angle(displ, m_ecc);
	if (m_ta > consts::PI) {
		m_ta -= consts::PI;
	}

	if (isElliptical()) {
		m_ma = meanFromTrue(m_ta, m_ecc.magnitude());
		m_meanAngular = sqrtf(m_body->gp() / (m_sma * m_sma * m_sma));
		m_period = consts::DPI / m_meanAngular;
	}
	else {
		m_ma = meanFromTrueHyp(m_ta, m_ecc.magnitude());
		m_meanAngular = sqrtf(-m_body->gp() / (m_sma * m_sma * m_sma));
	}

	m_time = m_ma / (m_sam.z > 0.0f ? -m_meanAngular : m_meanAngular);
}

void Orbit::updateWithinSOI(const Vector2f& position, const Vector2f& velocity) {
	Vector2f rv = velocity - m_body->getVelocity();
	Vector2f displ = position - m_body->getPosition();

	m_sam = Vector3f::cross(displ, rv);
	m_ecc = Vector3f::cross((Vector3f)rv, m_sam) / m_body->gp() - displ.normalized();
	m_tilt = atan2f(m_ecc.y, m_ecc.x);

	m_sma = 1.0f / (2.0f / displ.magnitude() - rv.sqrMagnitude() / m_body->gp());

	m_ta = Vector2f::angle(displ, m_ecc);
	if (m_ta > consts::PI) {
		m_ta -= consts::PI;
	}

	if (isElliptical()) {
		m_ma = meanFromTrue(m_ta, m_ecc.magnitude());
		m_meanAngular = sqrtf(m_body->gp() / (m_sma * m_sma * m_sma));
		m_period = consts::DPI / m_meanAngular;
	}
	else {
		m_ma = meanFromTrueHyp(m_ta, m_ecc.magnitude());
		m_meanAngular = sqrtf(-m_body->gp() / (m_sma * m_sma * m_sma));
	}

	m_time = m_ma / (m_sam.z > 0.0f ? -m_meanAngular : m_meanAngular);
}

void Orbit::progress(float dt) {
	m_time += dt;
	m_ma = m_time * (m_sam.z > 0.0f ? -m_meanAngular : m_meanAngular);

	if (isElliptical()) {
		while (m_time > m_period) {
			m_time -= m_period;
		}
		if (m_ma > consts::PI) {
			m_ma -= consts::DPI;
		}

		m_ea = eccentricFromMean(m_ma, m_ecc.magnitude());
		m_ta = trueFromEccentric(m_ea, m_ecc.magnitude());
	}
	else {
		m_ea = eccentricFromMeanHyp(m_ma, m_ecc.magnitude());
		m_ta = trueFromEccentricHyp(m_ea, m_ecc.magnitude());
	}
}

float Orbit::period() const {
	return m_period;
}

Vector2f Orbit::getPosition() const {
	float r = distanceFromBody();
	float ang = consts::DPI - m_ta + m_tilt;
	return Vector2f(
		r * cosf(ang),
		r * sinf(ang)
	) + m_body->getPosition();
}

Vector2f Orbit::getVelocity() const {
	float r = distanceFromBody();
	float speed = sqrtf(m_body->gp() * (2.0f / r - 1.0f / m_sma));

	float sinVr = m_sam.magnitude() / speed / r;
	float vr = asinf(sinVr);

	float angle = (m_ta > 0 ? vr : (consts::PI - vr)) - m_tilt + m_ta + consts::PI / 2;

	return Vector2f(
		speed * sinf(angle),
		speed * cosf(angle) 
	) * (m_sam.z > 0.0f ? -1.0f : 1.0f); 
}

Vector3f Orbit::eccVec() const {
	return m_ecc;
}

float Orbit::eccentricity() const {
	return m_ecc.magnitude();
}

float Orbit::semiMajorAxis() const {
	return m_sma;
} 

float Orbit::semiMinorAxis() const {
	return m_sma * sqrtf(1 - m_ecc.sqrMagnitude());
}

float Orbit::tilt() const {
	return m_tilt;
}

float Orbit::trueAnomaly() const {
	return m_ta;
}

float Orbit::eccentricAnomaly() const {
	return m_ea;
}

float Orbit::meanAnomaly() const {
	return m_ma;
}

float Orbit::time() const {
	return m_time;
}

CelestialBody* Orbit::body() const {
	return m_body;
}

float Orbit::periapsis() const {
	return m_sma * (1 - m_ecc.magnitude());
}

float Orbit::apoapsis() const {
	return m_sma * (1 + m_ecc.magnitude());;
}

float Orbit::sam() const {
	return m_sam.z;
}

float Orbit::distanceFromBody() const {
	return m_sam.sqrMagnitude() / m_body->gp() / (1.0f + m_ecc.magnitude() * cosf(m_ta));
}

bool Orbit::isElliptical() const {
	return m_ecc.sqrMagnitude() < 1.0f;
}

bool Orbit:: isHyperbolic() const {
	return m_ecc.sqrMagnitude() > 1.0f;
}