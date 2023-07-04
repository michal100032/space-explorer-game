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
	
	m_orbRenderer = Window::createObject<OrbitRenderer>();
	m_orbRenderer->setOrbit(&m_orbit);

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
		Window::createText("Tilt: " + std::to_string(m_orbit.tilt() * consts::RDEG), 300, 5, "Consolas", 15, sf::Color::White);
	m_stats[5] =
		Window::createText("Time: " + std::to_string(m_orbit.time()), 300, 25, "Consolas", 15, sf::Color::White);

	m_stats[6] =
		Window::createText("TA: " + std::to_string(m_orbit.trueAnomaly() * consts::RDEG), 450, 5, "Consolas", 15, sf::Color::White);
	m_stats[7] =
		Window::createText("EA: " + std::to_string(m_orbit.eccentricAnomaly() * consts::RDEG), 450, 25, "Consolas", 15, sf::Color::White);
	m_stats[8] =
		Window::createText("MA: " + std::to_string(m_orbit.meanAnomaly() * consts::RDEG), 600, 5, "Consolas", 15, sf::Color::White);

}

void Spacecraft::update() {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_angularSpeed -= c_angularAcceleration * Time::delta();
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_angularSpeed += c_angularAcceleration * Time::delta();
	} else {
		m_angularSpeed += -m_angularSpeed *
			(1.0f - c_angularDecceleration) * Time::delta();
	}

	m_rotation += m_angularSpeed * Time::delta();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Vector2f acc = {
			Time::delta() * c_acceleration * cosf(1.5f * consts::PI - m_rotation),
			Time::delta() * c_acceleration * sinf(1.5f * consts::PI - m_rotation)
		};
		m_orbit.accelerate(acc);
		m_orbRenderer->refresh();
	}

	m_orbit.progress(Time::delta());

	m_position = m_orbit.getPosition();

	m_stats[5]->setString("Time: " + std::to_string(m_orbit.time()));

	m_stats[6]->setString("TA: " + std::to_string(m_orbit.trueAnomaly() * consts::RDEG));
	m_stats[7]->setString("EA: " + std::to_string(m_orbit.eccentricAnomaly() * consts::RDEG));
	m_stats[8]->setString("MA: " + std::to_string(m_orbit.meanAnomaly() * consts::RDEG));

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
