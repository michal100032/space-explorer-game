#pragma once
#include <SFML/Graphics.hpp>

#include "../Orbit/Orbit.h"

class EllipseShape : public sf::Shape {
private:
    Orbit* m_orbit;

    float m_semiMajorAxis;
    float m_semiMinorAxis;

    float m_tilt;

    size_t m_pointCount = 30;
public:
    EllipseShape(Orbit* m_orbit);
    size_t getPointCount() const override;
    sf::Vector2f getPoint(size_t index) const override;

    void setOriginToFocus(int focus = 0);
    void setOriginToCenter();
};

