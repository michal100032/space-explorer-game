#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
	bool m_cameraDrag = false;
	sf::Vector2i m_dragStartMouse;
	sf::Vector2f m_dragStartCamera;

	sf::Vector2f m_position;
	float m_pixelsPerUnit = 10.0f;

public:
	Camera();

	void render();
	float getPixelsPerUnit();
	void setPixelsPerUnit(float value);

	void zoomIn();
	void zoomOut();
};

