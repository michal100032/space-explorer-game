#include "TestObject.h"

TestObject::TestObject() : Object("Test"), m_shape(60.0f, 40.0f, 3.14159f / 3) {
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineColor(sf::Color::Red);
	m_shape.setOutlineThickness(4.0f);
}

sf::Shape* TestObject::getShape() {
	return &m_shape;
}

void TestObject::update() {
	m_rotation += 0.3f;
}
