#pragma once

#include "renderer.h"
#include "screen.h"
#include "world.h"
#include "camera.h"
#include <vector>
#include <string>
#include <iostream>

namespace Sanches_project {

class Application {
public:
    Application(int width, int height, Camera& cam, std::string name);
    void exec();

    void add_object(const Object& source);

private:

    RasterScreen screen;
    sf::RenderWindow window;
    std::string frame_name;
    Renderer render;
    Camera camera;
    World world;

    void set_picture();

    void draw_objects();

    void event_handler(sf::Keyboard::Key key);
};

}//namespace Sanches_project