#include "init.h"

#include "Window/Window.h"
#include "Object/CelestialBody.h"
#include "Object/Spacecraft.h"
#include "Object/OrbitRenderer.h"

void init::celestialBodies() {
    CelestialBody* planet =
        Window::createObject<CelestialBody>("Planet", 20.0f, 10.0f, sf::Color(9, 150, 21));
    CelestialBody* moon =
        Window::createObject<CelestialBody>("Moon", 1.0f, 1.5f, sf::Color(212, 206, 106));

    planet->addChild(moon, 60.0f, 0.0f);

    Window::forEachObject([](Object* obj) -> void {
        if (strcmp(typeid(*obj).name(), "class CelestialBody") == 0) {
            ((CelestialBody*)obj)->calculateSoi();
        }
    });
}

void init::spacecraft() {
    Spacecraft* craft =
        Window::createObject<Spacecraft>(
            "Spacecraft",
            Vector2f(-10.0f, 10.0f),
            Vector2f(0.06f, 0.04f)
        );
}
