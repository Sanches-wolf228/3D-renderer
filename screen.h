#pragma once

#include <SFML/Graphics.hpp>

namespace Sanches_project {

class RasterScreen {
public:

	void pick_pixel(int w, int h, float depth, sf::Color color);

	RasterScreen(int w, int h);

	void draw(sf::RenderWindow& window);

	bool pixel_on_screen(int w, int h);

	void clear();

	int get_width();
	int get_height();

private:

	int width;
	int height;
	std::vector<sf::RectangleShape> pixels;
	std::vector<float> z_buffer;

	static constexpr int up_boarder = 600;
	static constexpr int down_boarder = 120;

	int trim_width(int w);

	int trim_height(int h);
};

}//namespace Sanches_project