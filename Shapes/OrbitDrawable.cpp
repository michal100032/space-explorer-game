#include "OrbitDrawable.h"
#include "../constants.h"

#include <iostream>

OrbitDrawable::OrbitDrawable(const Orbit& orbit) :
	m_orbit(orbit),
	m_buffer(sf::PrimitiveType::TriangleStrip, sf::VertexBuffer::Usage::Dynamic) {
	m_buffer.create(2 * OR_RESOLUTION);
	for (int i = 0; i < 2 * OR_RESOLUTION; i++)
		m_vertices[i].color = sf::Color(40, 40, 40);
	refresh();
}

void OrbitDrawable::refresh() {
	calcProperties();

	if (isClosed()) {
		calcVerticesClosed();
	} else {
		calcVerticesOpen();
	}
	m_buffer.update(m_vertices);
}

void OrbitDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_buffer, states);
}

void OrbitDrawable::calcProperties() {
	m_ecc = m_orbit.eccentricity();
	m_tilt = m_orbit.tilt();
	m_sma = m_orbit.semiMajorAxis();
	m_slr = m_sma * (1.0f - m_ecc * m_ecc);

	float val = 1.0f / m_ecc * (m_slr / m_orbit.body()->soi() - 1.0f);
	m_maxAngle = val > -1.0f ? (acosf(val) - 0.00001f) : -1.0f;
}

void OrbitDrawable::calcVerticesOpen() {
	static constexpr int POINT_COUNT = OR_RESOLUTION - 1;
	for (int i = 0; i < OR_RESOLUTION; i++) {
		float angle = 2 * m_maxAngle * i / POINT_COUNT - m_maxAngle;

		float dist = m_slr / (1.0f + m_ecc * cosf(angle));
		float dist2 = dist - OR_WIDTH;

		float cosAn = cosf(angle + m_tilt), sinAn = sinf(angle + m_tilt);
		m_vertices[2 * i].position.x = dist * cosAn;
		m_vertices[2 * i].position.y = -dist * sinAn;

		m_vertices[2 * i + 1].position.x = dist2 * cosAn;
		m_vertices[2 * i + 1].position.y = -dist2 * sinAn;
	}
}

void OrbitDrawable::calcVerticesClosed() {
	static constexpr int POINT_COUNT = OR_RESOLUTION - 1;
	for (int i = 0; i < OR_RESOLUTION; i++) {
		float angle = consts::DPI * i / POINT_COUNT;

		float dist = m_slr / (1.0f + m_ecc * cosf(angle));
		float dist2 = dist - OR_WIDTH;

		float cosAn = cosf(angle + m_tilt), sinAn = sinf(angle + m_tilt);
		m_vertices[2 * i].position.x = dist * cosAn;
		m_vertices[2 * i].position.y = -dist * sinAn;

		m_vertices[2 * i + 1].position.x = dist2 * cosAn;
		m_vertices[2 * i + 1].position.y = -dist2 * sinAn;
	}
}

bool OrbitDrawable::isClosed() {
	return m_maxAngle < 0.0f;
}
