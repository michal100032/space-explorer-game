#pragma once

#include <SFML/Graphics.hpp>

class Time {
private:
	static float m_delta;
	static float m_scale;

	static sf::Text* m_text;
public:
	static void init();

	static void setDelta(float delta);
	static float delta();
	
	static void setScale(float scale);
	static float scale();
};