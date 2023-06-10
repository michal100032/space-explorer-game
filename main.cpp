#include "Window/Window.h"
#include "Object/CelestialBody.h"
#include "Object/Spacecraft.h"
#include "Object/TestObject.h"


#include <iostream>
#include <cstring>

#include "Math/Vector2f.h"

int main()
{
    Vector2f a(5.0f, -5.0f);
    Vector2f b(10.0f, 3.33f);
    Vector2f c = a + b;

    std::cout << c << std::endl;

    Window::init("Hello there", 800, 600);
    
    CelestialBody* planet = 
        Window::createObject<CelestialBody>("Planet", 20.0f, 10.0f, sf::Color::Green);
    CelestialBody* moon =
        Window::createObject<CelestialBody>("Moon", 2.0f, 2.0f, sf::Color::White);

    planet->addChild(moon, 50.0f);

    Spacecraft* craft = Window::createObject<Spacecraft>("Spacecraft", sf::Color::Magenta);
    
    //Window::createObject<TestObject>();

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