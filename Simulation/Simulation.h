#pragma once

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "../Object/CelestialBody.h"
#include "../Orbit/Orbit.h"

#include "../Math/Vector2f.h"

class Simulation {
public:

	struct Encounter {
		CelestialBody* body;
		Vector2f position;
		float time;
		
		Encounter(CelestialBody* body, const Vector2f& position, float time);
	};


	struct Results {
		enum class Status {
			Unready,
			Ready,
			Seen,
		};

		Status status = Status::Seen;
		std::vector<Simulation::Encounter> encounters;
	};

	static Simulation& get() {
		static Simulation sim;
		return sim;
	}
	static void simulate(Orbit* orbit, float duration, float currTime, Results* info);

private:
	std::thread m_simulationThread;
	void beginSimulate(Orbit* orbit, float duration, float currTime, Results* results);
	void runSimulation();
	void loop();

	Results* m_results = nullptr;
	Orbit* m_orbit = nullptr;
	float m_duration = 0.0f;
	float m_currTime = 0.0f;
	bool m_running = false;
	bool m_abort = false;
	bool m_threadRunning = false;

	Vector2f getPosition(float time, Orbit* orbit);

	std::mutex m_mutex;
	std::condition_variable m_cv;
};