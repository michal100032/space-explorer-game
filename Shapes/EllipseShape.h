#pragma once
#include <SFML/Graphics.hpp>

class EllipseShape : public sf::Shape {
private:
    float m_semiMajorAxis;
    float m_semiMinorAxis;

    float m_tilt;
public:
	EllipseShape(float semiMajorAxis, float semiMinorAxis, float tilt);
    virtual unsigned int getPointCount() const;
    virtual sf::Vector2f getPoint(unsigned int index) const;
    void setOriginToFocus(int focus = 0);
};

