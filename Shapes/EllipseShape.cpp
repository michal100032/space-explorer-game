#include "EllipseShape.h"

EllipseShape::EllipseShape(Orbit* orbit) : 
    m_semiMajorAxis(orbit->semiMajorAxis()),
    m_semiMinorAxis(orbit->semiMinorAxis()),
    m_tilt(orbit->tilt()),
    m_orbit(orbit) {
    update();
}

size_t EllipseShape::getPointCount() const {
    return m_pointCount;
}

sf::Vector2f EllipseShape::getPoint(size_t index) const {
    float x = 
        m_semiMajorAxis * cosf(2 * 3.14159f * index / m_pointCount) * cosf(m_tilt)
        - m_semiMinorAxis * sinf(2 * 3.14159f * index / m_pointCount) * sinf(m_tilt);
    float y =
        m_semiMajorAxis * cosf(2 * 3.14159f * index / m_pointCount) * sinf(m_tilt) 
        + m_semiMinorAxis * sinf(2 * 3.14159f * index / m_pointCount) * cosf(m_tilt);
    
    return sf::Vector2f(x, -y);
}

void EllipseShape::setOriginToFocus(int focus) {
    sf::Vector2f shiftBy = (focus ? -1.0f : 1.0f) *
        m_orbit->eccVec().sf2() * m_semiMajorAxis;
    shiftBy.y *= -1;

    this->setOrigin(shiftBy);
}

void EllipseShape::setOriginToCenter()
{
}
