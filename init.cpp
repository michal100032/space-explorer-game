#include "init.h"

#include "Window/Window.h"
#include "Object/CelestialBody.h"
#include "Object/Spacecraft.h"
#include "Object/OrbitRenderer.h"

void init::celestialBodies() {
    CelestialBody* planet =
        Window::createObject<CelestialBody>("Planet", 20.0f, 10.0f, sf::Color::Green);
    CelestialBody* moon =
        Window::createObject<CelestialBody>("Moon", 2.0f, 2.0f, sf::Color::White);

    planet->addChild(moon, 50.0f);

    Window::forEachObject([](Object* obj) -> void {
        if (strcmp(typeid(*obj).name(), "class CelestialBody") == 0) {
            ((CelestialBody*)obj)->calculateSoi();
        }
    });
}

void init::spacecraft() {
    Spacecraft* craft =
        Window::createObject<Spacecraft>(
            Vector2f(-10.0f, 15.0f),
            Vector2f(0.05f, 0.03f)
        );
    /*
    OrbitRenderer* renderer =
        Window::createObject<OrbitRenderer>();
    renderer->setOrbit(craft->getOrbit());
    */
}
