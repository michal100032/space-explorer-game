#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Object {
protected:
	sf::Vector2f m_position;
	float m_rotation;

	std::string m_name;

	bool m_preserveScreenSize = false;
protected:
	Object(const std::string& name);
public:

	virtual void update() = 0;

	virtual sf::Vector2f getPosition();
	virtual void setPosition(float x, float y);
	virtual void move(float x, float y);

	virtual float getRotation();
	virtual void setRotation(float rotation);
	virtual void rotate(float angle);

	virtual sf::Shape* getShape() = 0;

	virtual const std::string& getName();
	virtual void setName(const std::string& name);

	bool preserveScreenSize();
};