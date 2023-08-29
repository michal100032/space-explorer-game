#include "ShapeObject.h"

ShapeObject::ShapeObject(const std::string& name)
	: Object(name) { }

sf::Drawable* ShapeObject::getDrawable() {
	return m_shape;
}

sf::Shape* ShapeObject::getShape() {
	return m_shape;
}

ShapeObject::~ShapeObject() {
	delete m_shape;
}
