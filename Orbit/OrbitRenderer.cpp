#include "OrbitRenderer.h"

#include "../Shapes/EllipseShape.h"

OrbitRenderer::OrbitRenderer(Orbit* orbit) 
	: Object("Orbit renderer"),
	m_orbit(orbit),
	m_color(40, 40, 40, 255) {}

void OrbitRenderer::refresh() {
	m_shape = new EllipseShape(
		m_orbit->semiMajorAxis(),
		m_orbit->semiMinorAxis(),
		m_orbit->tilt()
	);

	m_shape->setFillColor(sf::Color::Transparent);
	m_shape->setOutlineColor(m_color);
	m_shape->setOutlineThickness(3.0f);
}

sf::Shape* OrbitRenderer::getShape() {
	return m_shape;
}

OrbitRenderer::~OrbitRenderer()
{
}
