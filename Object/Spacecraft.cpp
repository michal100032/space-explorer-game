#include "Spacecraft.h"

#include <iostream>
#include <string>

#include "../Window/Time.h"
#include "../Window/Window.h"

#include "../constants.h"

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
	

	// STATS
	m_stats[0] = 
		Window::createText("SMA: " + std::to_string(m_orbit.semiMajorAxis()), 5, 5, "Consolas", 15, sf::Color::White);
	m_stats[1] =
		Window::createText("Ecc: " + std::to_string(m_orbit.eccentricity()), 5, 25, "Consolas", 15, sf::Color::White);
	m_stats[2] =
		Window::createText("Apoapsis: " + std::to_string(m_orbit.apoapsis()), 130, 5, "Consolas", 15, sf::Color::White);
	m_stats[3] =
		Window::createText("Periapsis: " + std::to_string(m_orbit.periapsis()), 130, 25, "Consolas", 15, sf::Color::White);
	m_stats[4] =
		Window::createText("TA: " + std::to_string(m_orbit.trueAnomaly()), 300, 5, "Consolas", 15, sf::Color::White);
	m_stats[5] =
		Window::createText("TA: " + std::to_string(m_orbit.tilt() * consts::RDEG), 300, 25, "Consolas", 15, sf::Color::White);

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
