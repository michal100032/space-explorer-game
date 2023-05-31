#include "Window.h"

#include <iostream>

Window::Window() {
	
}

Window& Window::inst() {
	static Window window;
	return window;
}

void Window::init(const std::string& title, int width, int height) {
	inst().m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	inst().m_width = width;
	inst().m_height = height;

	inst().m_camera = new Camera();
}

bool Window::isOpen() {
	return inst().m_window->isOpen();
}

void Window::handleEvents() {
	sf::Event event;
	while (inst().m_window->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			inst().m_window->close();
			break;
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.delta > 0) {
				inst().m_camera->zoomIn();
			} else inst().m_camera->zoomOut();
			break;
		}
	}
}

void Window::updateObjects() {
	for (Object* object : inst().m_objects) {
		object->update();
	}
}

void Window::display() {
	inst().m_camera->render();
}

void Window::close() {
	for (Object* object : inst().m_objects) {
		delete object;
	}

	delete inst().m_window;
	delete inst().m_camera;
}

void Window::forEachObject(void(*func)(Object*)) {
	for (Object* obj : inst().m_objects) {
		func(obj);
	}
}

Camera& Window::camera() {
	return *inst().m_camera;
}

int Window::width() {
	return inst().m_width;
}

int Window::height() {
	return inst().m_height;
}
