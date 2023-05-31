#include "CelestialBody.h"

#include <iostream>
#include <limits>

#include "../constants.h"

CelestialBody::CelestialBody(const std::string& name, float mass, float radius, sf::Color color) :
	Object(name), m_mass(mass), m_radius(radius), m_shape(radius) {
	m_shape.setFillColor(color);
    m_shape.setOrigin(m_shape.getLocalBounds().width / 2, m_shape.getLocalBounds().height / 2);
}

void CelestialBody::update() {
    const float dt = 1.0f / 60.0f;

    if (m_orbitalPeriod > 0) {
        m_orbitalTime += dt;
        if (m_orbitalTime > m_orbitalPeriod)
            m_orbitalTime -= m_orbitalPeriod;

        m_position.x = m_orbitalRadius * cosf(m_orbitalTime / m_orbitalPeriod * 2 * 3.14159f) + m_parent->m_position.x;
        m_position.y = -m_orbitalRadius * sinf(m_orbitalTime / m_orbitalPeriod * 2 * 3.14159f) + m_parent->m_position.y;
    }
}

void CelestialBody::calculateSoi() {
    if (m_orbitalPeriod <= 0)
        m_soi = std::numeric_limits<float>::max();
    else m_soi = m_orbitalRadius / (m_parent->m_mass / m_mass - 1) * (sqrtf(m_parent->m_mass / m_mass) - 1);

    std::cout << "SOI: " << m_soi << std::endl;
}

void CelestialBody::addChild(CelestialBody* child, float radius) {
    m_children.push_back(child);
    child->m_parent = this;
    child->m_orbitalRadius = radius;
    child->m_orbitalPeriod = 2 * 3.14159f * radius * sqrtf(radius / consts::G / m_mass);
}

sf::Shape* CelestialBody::getShape() {
	return (sf::Shape*)&m_shape;
}
