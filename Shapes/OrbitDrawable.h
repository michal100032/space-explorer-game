#pragma once

#include <SFML/Graphics.hpp>

#include "../Orbit/Orbit.h"

constexpr int OR_RESOLUTION = 100;
constexpr float OR_WIDTH = 0.5f;

class OrbitDrawable : public sf::Drawable {
public:
	OrbitDrawable(const Orbit& orbit);

	void refresh();
	bool isClosed();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	const Orbit& m_orbit;
	sf::VertexBuffer m_buffer;

	sf::Vertex m_vertices[2 * OR_RESOLUTION];

	// orbit properties
	float m_tilt = 0.0f;
	float m_sma = 0.0f;
	float m_ecc = 0.0f;
	float m_slr = 0.0f;

	float m_maxAngle;

	void calcProperties();
	void calcVerticesOpen();
	void calcVerticesClosed();

};