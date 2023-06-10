#pragma once
#include <SFML/Graphics.hpp>

class EllipseShape : public sf::Shape {
private:
    float m_semiMajorAxis;
    float m_semiMinorAxis;

    float m_tilt;

    size_t m_pointCount = 30;
public:
    EllipseShape(float semiMajorAxis, float semiMinorAxis, float tilt);
    size_t getPointCount() const override;
    sf::Vector2f getPoint(size_t index) const override;

    void setOriginToFocus(int focus = 0);
    void setOriginToCenter();
};

