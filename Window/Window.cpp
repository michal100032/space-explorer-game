#include "Window.h"

#include <iostream>

#include "Time.h"
#include "Text/Fonts.h"

Window::Window() {
	
}

void Window::loadFont(const std::string& name, const std::string& filename) {
	sf::Font font;
	if (!font.loadFromFile(filename)) {
		std::cout << "Error: font " << name << " could not be loaded" << std::endl;
	} else {
		m_fonts.push_back(font);
		m_fontsMap.insert({ name, &m_fonts[m_fonts.size() - 1] });
	}
}

Window& Window::inst() {
	static Window window;
	return window;
}

void Window::init(const std::string& title, int width, int height) {
	inst().m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	inst().m_window->setVerticalSyncEnabled(true);

	inst().m_width = width;
	inst().m_height = height;

	inst().m_camera = new Camera();

	inst().m_fonts.reserve(8);
	
	inst().loadFont("Consolas", "res/fonts/consola.ttf");
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
	Time::setDelta(1.0f / 60);

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

Text* Window::createText(const std::string& text, int x, int y, const std::string& fontFamily, int fontSize) {

	Text* t = new Text(text, x, y, inst().m_fontsMap[fontFamily], fontSize);

	inst().m_texts.push_back(t);
	return t;
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
