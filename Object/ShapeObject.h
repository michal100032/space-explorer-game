#pragma once

#include "Object.h"

class ShapeObject : public Object {
public:
	ShapeObject(const std::string& name);

	sf::Drawable* getDrawable() override;
	sf::Shape* getShape();

	template <typename T, typename... Args>
	void setShape(Args... args) {
		m_shape = new T(args...);
	}
	~ShapeObject();
private:
	sf::Shape* m_shape = nullptr;

};