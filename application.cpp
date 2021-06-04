#include "application.h"

namespace Sanches_project {

Application::Application(int width, int height, std::string name) : screen(RasterScreen(width, height)) {
    window.create(sf::VideoMode(screen.width, screen.height), name);
};

void Application::exec() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    draw_objects();
                    break;
                }
            }
        }
        set_picture();
    }
}

void Application::add_triangle(const Triangle& source) {
    objects.push_back(source);
}

void Application::set_picture() {
    screen.draw(window);
    window.display();
}

void Application::draw_objects() {
    for (const Triangle &t : objects) {
        render.draw(t, &screen);
    }
}

}//namespace Sanches_project