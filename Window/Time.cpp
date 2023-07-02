#include "Time.h"

float Time::m_delta = 0.0f;

void Time::setDelta(float delta) {
	m_delta = delta;
}
float Time::delta() {
	return m_delta;
}