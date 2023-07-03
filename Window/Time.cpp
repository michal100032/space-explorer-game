#include "Time.h"

#include "Window.h"

float Time::m_delta = 0.0f;
float Time::m_scale = 1.0f;
sf::Text* Time::m_text = nullptr;

void Time::init() {
	m_text = Window::createText("x1", Window::width() - 130, Window::height() - 25, "Consolas", 15, sf::Color::Green);
}

void Time::setDelta(float delta) {
	m_delta = delta;
}
float Time::delta() {
	return m_delta * m_scale;
}

void Time::setScale(float scale){
	m_scale = scale;
	m_text->setString("x" + std::to_string(scale));
}

float Time::scale() {
	return m_scale;
}
