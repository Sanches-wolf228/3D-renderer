#include "application.h"

namespace Sanches_project {

Application::Application(int width, int height, Camera &cam, std::string name) : screen(RasterScreen(width, height)), camera(cam) {
    camera.set_ratio(((float)screen.get_height()) / screen.get_width());
    render.set_parameters(&screen, &camera);
    window.create(sf::VideoMode(screen.get_width(), screen.get_height()), name);
};

void Application::exec() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                event_handler(event.key.code);
            }
        }
        set_picture();
    }
}

void Application::add_object(const Object& source) {
    world.add(source);
}

void Application::set_picture() {
    screen.draw(window);
    window.display();
}

void Application::draw_objects() {
    for (Object &obj : world.data) {
        for (Triangle t : obj.data) {
            render.draw(t);
        }
    }
}

void Application::event_handler(sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::Left:
        std::cout << "Left\n";
        camera.vertical_rotate(pi / 36);
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::Right:
        std::cout << "Right\n";
        camera.vertical_rotate(-pi / 36);
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::Up:
        std::cout << "Up\n";
        camera.horizontal_rotate(-pi / 36);
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::Down:
        std::cout << "Down\n";
        camera.horizontal_rotate(pi / 36);
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::U:
        camera.move_location({ 0, 0, 1 });
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::D:
        camera.move_location({ 0, 0, -1 });
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::L:
        camera.move_location({ 0, -1, 0 });
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::R:
        camera.move_location({ 0, 1, 0 });
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::F:
        camera.move_location({ 1, 0, 0 });
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::B:
        camera.move_location({ -1, 0, 0 });
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::Equal:
        std::cout << "Zoom+\n";
        camera.zoom(-pi/12);
        screen.clear();
        draw_objects();
        break;
    case sf::Keyboard::Divide:
        std::cout << "Zoom-\n";
        camera.zoom(pi / 12);
        screen.clear();
        draw_objects();
        break;
    }


}

}//namespace Sanches_project