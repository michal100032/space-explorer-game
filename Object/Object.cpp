#include "Object.h"

#include <iostream>

Object::Object(const std::string& name) : m_name(name), m_rotation(0.0f) {

}

const std::string& Object::name() const {
	return m_name;
}

Vector2f Object::getPosition() {
	return m_position;
}

void Object::setPosition(float x, float y) {
	m_position.x = x; m_position.y = y;
}

void Object::move(float x, float y) {
	m_position.x += x; m_position.y += y;
}

float Object::getRotation() {
	return m_rotation;
}

void Object::setRotation(float rotation) {
	m_rotation = rotation;
}

void Object::rotate(float angle) {
	m_rotation += angle;
}

void Object::setName(const std::string& name) {
	m_name = name;
}

bool Object::preserveScreenSize() {
	return m_preserveScreenSize;
}
