#include "Camera.h"
#include "Window.h"
#include <iostream>

#include "../constants.h"

Camera::Camera()
{
}

void Camera::render() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (m_cameraDrag) {
            sf::Vector2i mouseRel = sf::Mouse::getPosition() - Window::inst().m_window->getPosition();
            m_position = sf::Vector2f(m_dragStartMouse.x - mouseRel.x, mouseRel.y - m_dragStartMouse.y) / m_pixelsPerUnit + m_dragStartCamera;
        } else {
            m_dragStartMouse = sf::Mouse::getPosition() - Window::inst().m_window->getPosition();
            if (m_dragStartMouse.x >= 0 && m_dragStartMouse.y >= 0) {
                m_cameraDrag = true;
                m_dragStartCamera = m_position;
            }
        }
    }
    else if (m_cameraDrag) m_cameraDrag = false;

    Window::inst().m_window->clear();
    for (Object* object : Window::inst().m_objects) {
        if (!object->isActive())
            continue;
        sf::Transform transform;
        transform.translate(
            Window::width() / 2 + (object->getPosition().x - m_position.x) * m_pixelsPerUnit,
            Window::height() / 2 + (m_position.y - object->getPosition().y) * m_pixelsPerUnit
        );
        if (!object->preserveScreenSize())
            transform.scale(m_pixelsPerUnit, m_pixelsPerUnit);
        transform.rotate(object->getRotation() * consts::RDEG);
        sf::RenderStates states;
        states.transform = transform;
        Window::inst().m_window->draw(*object->getDrawable(), transform);
    }
}

float Camera::getPixelsPerUnit() {
	return m_pixelsPerUnit;
}

void Camera::setPixelsPerUnit(float value) {
    m_pixelsPerUnit = value;
}

void Camera::zoomIn() {

    sf::Vector2f pixDist = (sf::Vector2f)(
        sf::Mouse::getPosition()
        - Window::inst().m_window->getPosition()
        - sf::Vector2i(Window::width() / 2, Window::height() / 2));
    pixDist.y *= -1;

    pixDist *= (1.2f - 1.0f);
    pixDist /= m_pixelsPerUnit;
    m_position += pixDist;
    m_pixelsPerUnit *= 1.2f;
}

void Camera::zoomOut() {
    sf::Vector2f pixDist = (sf::Vector2f)(
        sf::Mouse::getPosition()
        - Window::inst().m_window->getPosition()
        - sf::Vector2i(Window::width() / 2, Window::height() / 2));
    pixDist.y *= -1;

    pixDist *= (1.0f - 1.0f / 1.2f);
    pixDist /= m_pixelsPerUnit;
    m_position -= pixDist;
    m_pixelsPerUnit /= 1.2f;
}
