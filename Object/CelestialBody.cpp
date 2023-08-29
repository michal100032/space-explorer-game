#include "CelestialBody.h"

#include <iostream>
#include <limits>

#include "../constants.h"
#include "../Window/Window.h"
#include "../Window/Time.h"

CelestialBody* CelestialBody::root = nullptr;

CelestialBody::CelestialBody(const std::string& name, float mass, float radius, sf::Color color) :
	Object(name), m_mass(mass), m_radius(radius), m_shape(radius), m_gp(consts::G * mass) {

    m_shape.setFillColor(color);
    m_shape.setOrigin(m_shape.getLocalBounds().width / 2, m_shape.getLocalBounds().height / 2);
}

void CelestialBody::update() {
    if (m_orbitalPeriod > 0) {
        m_orbitalTime += Time::delta();
        if (m_orbitalTime > m_orbitalPeriod)
            m_orbitalTime -= m_orbitalPeriod;

        m_position.x = m_orbitalRadius * cosf(m_orbitalTime * m_angularSpeed) + m_parent->m_position.x;
        m_position.y = -m_orbitalRadius * sinf(m_orbitalTime * m_angularSpeed) + m_parent->m_position.y;       
    
        m_soiSprite->setPosition(m_position.x, m_position.y);
    }
}

Vector2f CelestialBody::getVelocity() {
    if (m_orbitalPeriod <= 0.0f) {
        return { 0.0f, 0.0f };
    }
    
    return {
       -m_orbitalRadius * sinf(m_orbitalTime / m_orbitalPeriod * consts::DPI) / m_orbitalPeriod * consts::DPI,
       -m_orbitalRadius * cosf(m_orbitalTime / m_orbitalPeriod * consts::DPI) / m_orbitalPeriod * consts::DPI
    };
}

float CelestialBody::gp() {
    return m_gp;
}

void CelestialBody::calculateSoi() {
    if (m_orbitalPeriod <= 0) {
        m_soi = std::numeric_limits<float>::max();
        root = this;
    }
    else {
        m_soi = m_orbitalRadius * powf(m_mass / m_parent->m_mass, 0.4f);
        //m_soi = m_orbitalRadius / (m_parent->m_mass / m_mass - 1) * (sqrtf(m_parent->m_mass / m_mass) - 1);
        m_soiSprite = Window::createInsertObject<ShapeObject>("SOI sprite");
        m_soiSprite->setShape<sf::CircleShape>(m_soi);
        sf::Shape* shape = m_soiSprite->getShape();
        shape->setFillColor(sf::Color::Transparent);
        shape->setOutlineThickness(1.0f);
        shape->setOrigin(m_soi, m_soi);
        shape->setOutlineColor(sf::Color(20, 20, 20));
    }
}

void CelestialBody::addChild(CelestialBody* child, float radius, float initialAngle) {
    m_children.push_back(child);
    child->m_parent = this;
    child->m_orbitalRadius = radius;
    child->m_orbitalPeriod = consts::DPI * radius * sqrtf(radius / consts::G / m_mass);
    child->m_angularSpeed = consts::DPI / child->m_orbitalPeriod;
    child->m_orbitalTime = initialAngle / child->m_angularSpeed;

    child->m_position.x = radius + m_position.x;
    child->m_position.y = m_position.y;
}

sf::Drawable* CelestialBody::getDrawable() {
	return (sf::Shape*)&m_shape;
}

CelestialBody* CelestialBody::whoseSoi(Vector2f pos) {
    CelestialBody* curr = root;
    while (true) {
        for (CelestialBody* child : curr->m_children) {
            if (Vector2f::distance(pos, child->getPosition()) <= child->m_soi) {
                curr = child;
                break;
            }
        }
        return curr;
    }
    return nullptr;
}

Vector2f CelestialBody::gfs(Vector2f position) {
    Vector2f displacement = position - m_position;
    return -displacement.normalized() * m_gp / displacement.sqrMagnitude();
}

float CelestialBody::soi() {
    return m_soi;
}

float CelestialBody::mass() {
    return m_mass;
}

float CelestialBody::radius() {
    return m_radius;
}

CelestialBody* CelestialBody::parent() {
    return m_parent;
}

float CelestialBody::orbitalRadius() {
    return m_orbitalRadius;
}

uint32_t CelestialBody::colorInt() {
    return m_shape.getFillColor().toInteger();
}

float CelestialBody::orbitalAngle() {
    return m_orbitalTime * m_angularSpeed;
}
