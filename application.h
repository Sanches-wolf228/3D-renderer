#pragma once

#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "screen.h"
#include "figures.h"
#include <vector>
#include <string>

namespace Sanches_project {

class Application {
public:
    Application(int width, int height, std::string name);
    void exec();

    void add_triangle(const Triangle& source);

private:

    std::vector<Triangle> objects;
    RasterScreen screen;
    sf::RenderWindow window;
    std::string frame_name;
    Renderer render;

    void set_picture();

    void draw_objects();
};

}//namespace Sanches_project