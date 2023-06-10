#include "Spacecraft.h"

Spacecraft::Spacecraft(const std::string& name, sf::Color color) :
	Object(name), m_shape(3) {
	m_shape.setPoint(0, { -10, -15 });
	m_shape.setPoint(1, { 0,  15 });
	m_shape.setPoint(2, { 10, -15 });

	m_shape.setFillColor(color);

	m_shape.setOrigin(m_shape.getLocalBounds().width / 2, m_shape.getLocalBounds().height / 2);

	m_preserveScreenSize = true;

	m_position = { 30.0f, 30.0f };

	m_orbit.update(m_position, m_velocity);
	m_orbitRenderer = Window::createObject<OrbitRenderer>(&m_orbit);
}

void Spacecraft::update() {

}

sf::Shape* Spacecraft::getShape() {
	return (sf::Shape*)&m_shape;
}

Vector2f Spacecraft::getVelocity() {
	return m_velocity;
}
