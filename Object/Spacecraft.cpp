#include "Spacecraft.h"

#include <iostream>

#include "../Window/Time.h"

Spacecraft::Spacecraft(Vector2f position, Vector2f velocity) :
	Object("Spacecraft"), m_shape(3) {
	m_position = position;
	m_velocity = velocity;

	m_preserveScreenSize = true;

	m_shape.setPoint(0, { -10, -15 });
	m_shape.setPoint(1, { 0,  15 });
	m_shape.setPoint(2, { 10, -15 });
	
	m_shape.setFillColor(sf::Color::White);

	m_orbit.update(m_position, m_velocity);
	std::cout << "SMA: " << m_orbit.semiMajorAxis() << std::endl;
	std::cout << "Periapsis: " << m_orbit.periapsis() << std::endl;
	std::cout << "Apoapsis: " << m_orbit.apoapsis() << std::endl;
	std::cout << "Ecc: " << m_orbit.eccentricity() << std::endl;
	std::cout << "TA: " << m_orbit.trueAnomaly() << std::endl;
}

void Spacecraft::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_angularSpeed += c_angularAcceleration * Time::delta();
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_angularSpeed -= c_angularAcceleration * Time::delta();
	} else {
		m_angularSpeed += -m_angularSpeed *
			(1.0f - c_angularDecceleration) * Time::delta();
	}

	//std::cout << "dt: " << Time::delta() << " s" << std::endl;
	//std::cout << "m_angularSpeed: " << m_angularSpeed << std::endl;

	m_rotation += m_angularSpeed * Time::delta();
}

sf::Shape* Spacecraft::getShape() {
	return (sf::Shape*)&m_shape;
}

Orbit* Spacecraft::getOrbit() {
	return &m_orbit;
}

Vector2f Spacecraft::getVelocity() {
	return m_velocity;
}
