#include "Window/Window.h"
#include "Object/CelestialBody.h"
#include "Object/Spacecraft.h"

#include <iostream>
#include <cstring>

int main()
{
    Window::init("Hello there", 800, 600);

    CelestialBody* planet = 
        Window::createObject<CelestialBody>("Planet", 20.0f, 10.0f, sf::Color::Green);
    CelestialBody* moon =
        Window::createObject<CelestialBody>("Moon", 2.0f, 2.0f, sf::Color::White);

    planet->addChild(moon, 50.0f);

    Spacecraft* craft = Window::createObject<Spacecraft>("Spacecraft", sf::Color::Magenta);

    Window::forEachObject([](Object* obj) -> void {
        if (strcmp(typeid(*obj).name(), "class CelestialBody") == 0) {
            ((CelestialBody*)obj)->calculateSoi();
        }
    });
    
    while (Window::isOpen()) {   
        Window::handleEvents();
        Window::updateObjects();
        Window::display();
    }

    Window::close();

    return 0;
}