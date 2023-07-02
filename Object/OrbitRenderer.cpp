#include "OrbitRenderer.h"

#include "../Shapes/EllipseShape.h"

#include <iostream>

OrbitRenderer::OrbitRenderer()
	: Object("Orbit renderer"),
	m_color(40, 40, 40, 255) {}

void OrbitRenderer::refresh() {
	
	m_shape = new EllipseShape(m_orbit);

	m_shape->setFillColor(sf::Color::Transparent);
	m_shape->setOutlineColor(m_color);
	m_shape->setOutlineThickness(0.5f);

	((EllipseShape*)m_shape)->setOriginToFocus();
	
}

void OrbitRenderer::setOrbit(Orbit* orbit) {
	m_orbit = orbit;
	refresh();
}

sf::Shape* OrbitRenderer::getShape() {
	return m_shape;
}

OrbitRenderer::~OrbitRenderer()
{
}
