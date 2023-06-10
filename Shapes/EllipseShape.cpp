#include "EllipseShape.h"

EllipseShape::EllipseShape(float semiMajorAxis, float semiMinorAxis, float tilt)
    : m_semiMajorAxis(semiMajorAxis), m_semiMinorAxis(semiMinorAxis), m_tilt(tilt)
{
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
    
    return sf::Vector2f(x, y);
}

void EllipseShape::setOriginToFocus(int focus) {

}

void EllipseShape::setOriginToCenter()
{
}
