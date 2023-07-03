#include "Window.h"

#include <iostream>

#include "Time.h"

Window::Window() {
	
}

void Window::loadFont(const std::string& name, const std::string& filename) {
	sf::Font font;
	if (!font.loadFromFile(filename)) {
		std::cout << "Error: font " << name << " could not be loaded" << std::endl;
	} else {
		m_fonts.insert({ name, font });
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

	inst().m_window->setKeyRepeatEnabled(false);

	Time::init();
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
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Comma) {
				Time::setScale(Time::scale() / 2);
			} else if (event.key.code == sf::Keyboard::Period) {
				Time::setScale(Time::scale() * 2);
			} else if (event.key.code == sf::Keyboard::Slash) {
				Time::setScale(1.0f);
			}
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
	
	for (sf::Text* text : inst().m_texts) {
		inst().m_window->draw(*text);
	}
	Window::inst().m_window->display();
}

void Window::close() {
	for (Object* object : inst().m_objects) {
		delete object;
	}

	for (sf::Text* object : inst().m_texts) {
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

sf::Text* Window::createText(const std::string& text, float x, float y, const std::string& fontFamily, int fontSize, sf::Color color) {
	sf::Text* t = new sf::Text;
	t->setString(text);
	t->setCharacterSize(fontSize);
	t->setPosition(x, y);
	t->setFont(inst().m_fonts[fontFamily]);
	t->setFillColor(color);

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
