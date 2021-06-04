#pragma once

#include <SFML/Graphics.hpp>

namespace Sanches_project {

class RasterScreen {
public:

	void pick_pixel(int w, int h, double depth, sf::Color color);

	RasterScreen(int w, int h);

	void draw(sf::RenderWindow& window);

	int width;
	int height;

	bool pixel_on_screen(int w, int h);

private:
	std::vector<sf::RectangleShape> pixels;
	std::vector<double> z_buffer;

	static constexpr int up_boarder = 600;
	static constexpr int down_boarder = 120;

	int trim_width(int w);

	int trim_height(int h);
};

}//namespace Sanches_project