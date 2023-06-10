#pragma once
#include "Object.h"
#include "../Shapes/EllipseShape.h"

class TestObject : public Object
{
private:
	EllipseShape m_shape;
public:
	TestObject();
	sf::Shape* getShape() override;
	void update() override;
};

