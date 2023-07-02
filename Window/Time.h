#pragma once

class Time {
private:
	static float m_delta;
public:
	static void setDelta(float delta);
	static float delta();
};