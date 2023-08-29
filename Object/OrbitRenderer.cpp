#include "OrbitRenderer.h"

#include "../Window/Window.h"
#include "ShapeObject.h"

#include <iostream>

OrbitRenderer::OrbitRenderer(Orbit* orbit)
	: Object("Orbit renderer"), m_orbit(orbit), m_drawable(*orbit),
	m_color(40, 40, 40) {
	
	m_indicators[IND_ENC] = Window::createInsertObject<ShapeObject>("Encounter indicator");
	m_indicators[IND_PER] = Window::createInsertObject<ShapeObject>("Periapsis indicator");
	m_indicators[IND_APO] = Window::createInsertObject<ShapeObject>("Apoapsis indicator");
	for (int i = 0; i < 3; i++) {
		m_indicators[i]->setShape<sf::CircleShape>(1.0f);
		m_indicators[i]->getShape()->setOrigin(1.0f, 1.0f);
	}
	m_indicators[IND_ENC]->getShape()->setFillColor(sf::Color::Magenta);
	m_indicators[IND_PER]->getShape()->setFillColor(sf::Color::Red);
	m_indicators[IND_APO]->getShape()->setFillColor(sf::Color::Blue);

	m_indicators[IND_APO]->setActive(m_drawable.isClosed());
}

void OrbitRenderer::refresh() {
	m_drawable.refresh();
	m_indicators[IND_APO]->setActive(m_drawable.isClosed());
}

void OrbitRenderer::update() {
	Vector2f dir = m_orbit->eccVec().normalized();
	
	m_position = m_orbit->body()->getPosition();
	m_indicators[IND_PER]->setPosition(dir * m_orbit->periapsis() + m_position);
	if (m_drawable.isClosed()) {
		m_indicators[IND_APO]->setPosition(-dir * m_orbit->apoapsis() + m_position);
	}
	if (m_indicators[IND_ENC]->isActive()) {
		m_indicators[IND_ENC]->setPosition(m_encounterPosition + m_position);
	}
}

sf::Drawable* OrbitRenderer::getDrawable() {
	return &m_drawable;
}

void OrbitRenderer::setEncInd(bool active) {
	m_indicators[IND_ENC]->setActive(active);
}

void OrbitRenderer::setEncIndPosition(const Vector2f& position) {
	m_indicators[IND_ENC]->setActive(true);
	m_encounterPosition = position;
}

OrbitRenderer::~OrbitRenderer()
{

}
