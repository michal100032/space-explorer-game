#include "init.h"
#include "Window/Window.h"

int main()
{
    Window::init("Game", 800, 600);
    
    // init::celestialBodies();
    // init::spacecraft();
    
    while (Window::isOpen()) {   
        Window::handleEvents();
        Window::updateObjects();
        Window::display();
    }

    Window::close();

    return 0;
}