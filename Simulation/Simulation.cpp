#include "Simulation.h"

#include <thread>

#include "../constants.h"
#include "../Window/Window.h"

void Simulation::simulate(Orbit* orbit, float duration, float currTime, Results* results) {
	get().beginSimulate(orbit, duration, currTime, results);
}

void Simulation::beginSimulate(Orbit* orbit, float duration, float currTime, Results* results) {

	if (m_running) {
		m_abort = true;
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cv.wait(lock, [this] { return !m_running; });
	}

	results->encounters.clear();
	results->status = Results::Status::Unready;

	m_orbit = orbit;
	m_duration = duration;
	m_currTime = currTime;
	m_results = results;

	m_cv.notify_one();

	if (!m_threadRunning) {
		m_threadRunning = true;
		m_simulationThread = std::thread(&Simulation::loop, &get());
		m_simulationThread.detach();
	}
}

void Simulation::runSimulation() {
	m_running = true;
	int childCount = m_orbit->m_body->m_children.size();
	float* initialTimes = new float[childCount];
	for (int i = 0; i < childCount; i++) {
		initialTimes[i] = m_orbit->m_body->m_children[i]->m_orbitalTime;
	}
	
	const float timeStep = 6.0f;
	for (float t = 0.0f; t < m_duration; t += timeStep) {
		if (m_abort)
			break;

		Vector2f position = getPosition(t, m_orbit);
		if (Vector2f::distance(m_orbit->m_body->getPosition(), position) > m_orbit->m_body->m_soi) {
			m_results->encounters.emplace_back(m_orbit->m_body->m_parent, position - m_orbit->m_body->getPosition(), m_currTime + t);
			break;
		}
		for (int i = 0; i < childCount; i++) {
			CelestialBody* body = m_orbit->m_body->m_children[i];
			Vector2f bodyPosition = {
				body->m_orbitalRadius * cosf((t + initialTimes[i]) * body->m_angularSpeed),
				-body->m_orbitalRadius * sinf((t + initialTimes[i]) * body->m_angularSpeed)
			};
			if (Vector2f::distance(bodyPosition, position) <= body->m_soi) {
				m_results->encounters.emplace_back(body, position - m_orbit->m_body->getPosition(), m_currTime + t);
				goto br;
			}
		}
	}

	br:
	delete[] initialTimes;
	m_running = false;
	if (m_abort) {
		m_abort = false;
		m_cv.notify_one();
	}
	else m_results->status = Results::Status::Ready;
}

void Simulation::loop() {
	using namespace std::chrono_literals;

	while (Window::isOpen()) {
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_cv.wait(lock, [this] { return m_results != nullptr; });
		}
		runSimulation();
		m_results = nullptr;
	}
}

Vector2f Simulation::getPosition(float time, Orbit* orbit) {
	float ecc = orbit->eccentricity();
	float ma = time * orbit->m_meanAngular * (orbit->m_sam.z > 0.0f ? -1.0f : 1.0f) + orbit->m_ma;

	float ta = orbit->isElliptical() ? Orbit::trueFromMean(ma, ecc) : Orbit::trueFromMeanHyp(ma, ecc);

	float r = orbit->m_sam.sqrMagnitude() / orbit->m_body->gp() / (1.0f + ecc * cosf(ta));
	float ang = consts::DPI - ta + orbit->m_tilt;
	return Vector2f(
		r * cosf(ang),
		r * sinf(ang)
	) + orbit->m_body->getPosition();
}

Simulation::Encounter::Encounter(CelestialBody* body, const Vector2f& position, float time)
	: body(body), position(position), time(time)
{
}
