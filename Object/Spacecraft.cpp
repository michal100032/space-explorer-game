#include "Spacecraft.h"

#include <iostream>
#include <string>

#include "../Window/Time.h"
#include "../Window/Window.h"

#include "../constants.h"

Spacecraft::Spacecraft(const std::string& name, Vector2f position, Vector2f velocity) :
	Object(name, position), m_shape(3), m_velocity(velocity) {
	m_preserveScreenSize = true;

	m_orbit.update(m_position, m_velocity);
	
	m_orbRenderer = Window::createInsertObject<OrbitRenderer>(&m_orbit);
	
	initShape();
	initStats();
}

Spacecraft::Spacecraft(const std::string& name, const Orbit& orbit) :
	Object(name, { 0.0f, 0.0f }), m_shape(3), m_velocity(0.0f, 0.0f), m_orbit(orbit) {
	m_preserveScreenSize = true;

	m_orbRenderer = Window::createInsertObject<OrbitRenderer>(&m_orbit);

	initShape();
	initStats();
}

void Spacecraft::update() {
	
	updateRotation();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		accelerate();
	else updatePosition();
	
	if (m_results.status == Simulation::Results::Status::Ready)
		displaySimulationResults();

	updateStats();
}

void Spacecraft::accelerate() {
	Vector2f acc = Vector2f(
		Time::delta() * c_acceleration * cosf(1.5f * consts::PI - m_rotation),
		Time::delta() * c_acceleration * sinf(1.5f * consts::PI - m_rotation)
	) + m_orbit.body()->gfs(m_position) * Time::delta();
	m_velocity += acc;
	m_position += (m_orbit.body()->getVelocity() + m_velocity) * Time::delta();

	m_orbit.updateWithinSOI(m_position, m_orbit.body()->getVelocity() + m_velocity);
	updateOrbitStats();
	if (m_results.status == Simulation::Results::Status::Seen) {
		Simulation::simulate(&m_orbit, m_orbit.period(), m_orbit.time(), &m_results);
	}

	m_orbRenderer->refresh();
}

void Spacecraft::updateRotation() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_angularSpeed -= c_angularAcceleration * Time::delta();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_angularSpeed += c_angularAcceleration * Time::delta();
	}
	else {
		if (m_angularSpeed < 0.1f && m_angularSpeed > -0.1f)
			m_angularSpeed = 0.0f;
		else m_angularSpeed += -m_angularSpeed *
			(1.0f - c_angularDecceleration) * Time::delta();
	}

	m_rotation += m_angularSpeed * Time::delta();

	while (m_rotation > consts::DPI) {
		m_rotation -= consts::DPI;
	}
	while (m_rotation < 0) {
		m_rotation += consts::DPI;
	}
}

void Spacecraft::updatePosition() {
	m_orbit.progress(Time::delta());
	m_position = m_orbit.getPosition();
	m_velocity = m_orbit.getVelocity();

	if (soiEncounterExpected()) {
		makeEncounter();
	}
}

void Spacecraft::displaySimulationResults() {
	m_results.status = Simulation::Results::Status::Seen;

	if (m_results.encounters.size() > 0) {
		m_orbRenderer->setEncIndPosition(m_results.encounters[0].position);	
		m_encounterTime = m_results.encounters[0].time;
		m_stats[13]->setString("Encounter time: " + std::to_string(m_encounterTime));
		m_encounterExpected = true;
	}
	else {
		m_encounterExpected = false;
		m_orbRenderer->setEncInd(false);
		m_stats[13]->setString("Encounter time: -");
	}
}

bool Spacecraft::soiEncounterExpected() {
	return m_encounterExpected && m_orbit.time() > m_encounterTime;
}

void Spacecraft::makeEncounter() {
	CelestialBody* prevBody = m_orbit.body();
	m_orbit.update(m_position, m_velocity + prevBody->getVelocity());
	
	m_orbit.progress(Time::delta());
	m_position = m_orbit.getPosition();
	m_velocity = m_orbit.getVelocity();

	if (prevBody != m_orbit.body()) {
		m_orbRenderer->setEncInd(false);
		m_orbRenderer->refresh();
		m_encounterExpected = false;
		updateStats();
	}
	
	if (m_results.status == Simulation::Results::Status::Seen) {
		Simulation::simulate(&m_orbit, m_orbit.period(), m_orbit.time(), &m_results);
	}
}


void Spacecraft::initShape() {
	m_shape.setPoint(0, { -10, -9 });
	m_shape.setPoint(1, { 0,  16 });
	m_shape.setPoint(2, { 10, -9 });

	m_shape.setFillColor(sf::Color::White);
}

void Spacecraft::initStats() {
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
	m_stats[9] =
		Window::createText("x: ", 5, Window::height() - 80, "Consolas", 15, sf::Color::White);
	m_stats[10] =
		Window::createText("y: ", 110, Window::height() - 80, "Consolas", 15, sf::Color::White);
	m_stats[11] =
		Window::createText("vx: ", 5, Window::height() - 40, "Consolas", 15, sf::Color::White);
	m_stats[12] =
		Window::createText("vy: ", 110, Window::height() - 40, "Consolas", 15, sf::Color::White);

	m_stats[13] =
		Window::createText("Encounter time: -", 600, 25, "Consolas", 15, sf::Color::White);

}

void Spacecraft::updateOrbitStats() {
	m_stats[0]->setString("SMA: " + std::to_string(m_orbit.semiMajorAxis()));
	m_stats[1]->setString("Ecc: " + std::to_string(m_orbit.eccentricity()));
	m_stats[2]->setString("Apoapsis: " + std::to_string(m_orbit.apoapsis()));
	m_stats[3]->setString("Periapsis: " + std::to_string(m_orbit.periapsis()));
	m_stats[4]->setString("Tilt: " + std::to_string(m_orbit.tilt() * consts::RDEG));
}

void Spacecraft::updateStats() {
	m_stats[5]->setString("Time: " + std::to_string(m_orbit.time()));

	m_stats[6]->setString("TA: " + std::to_string(m_orbit.trueAnomaly() * consts::RDEG));
	m_stats[7]->setString("EA: " + std::to_string(m_orbit.eccentricAnomaly() * consts::RDEG));
	m_stats[8]->setString("MA: " + std::to_string(m_orbit.meanAnomaly() * consts::RDEG));

	m_stats[9]->setString("x: " + std::to_string(m_position.x));
	m_stats[10]->setString("y: " + std::to_string(m_position.y));

	m_stats[11]->setString("vx: " + std::to_string(m_velocity.x));
	m_stats[12]->setString("vy: " + std::to_string(m_velocity.y));
}


sf::Drawable* Spacecraft::getDrawable() {
	return (sf::Shape*)&m_shape;
}

Orbit* Spacecraft::getOrbit() {
	return &m_orbit;
}

Vector2f Spacecraft::getVelocity() {
	return m_velocity;
}
