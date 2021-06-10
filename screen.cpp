#include <SFML/Graphics.hpp>
#include <vector>
#include <cassert>
#include "screen.h"

namespace Sanches_project {

void RasterScreen::pick_pixel(int w, int h, float depth, sf::Color color) {
	assert(pixel_on_screen(w, h));
	if ((depth > 0) && (z_buffer[w + h * width] == -1 || depth < z_buffer[w + h * width])) {
		pixels[w + h * width].setFillColor(color);
		z_buffer[w + h * width] = depth;
	}
	return;
}

RasterScreen::RasterScreen(int w, int h) : width(trim_width(w)), height(trim_height(h)), pixels(width * height), z_buffer(width* height, -1) {

	// каждому пикселю экрана создаем прямоугольник 1*1 в нужном месте
	for (int i = 0; i != width; ++i) {
		for (int j = 0; j != height; ++j) {
			pixels[i + j * width].setSize(sf::Vector2f(1.f, 1.f));
			pixels[i + j * width].setPosition(float(i), float(j));
		}
	}
}

void RasterScreen::draw(sf::RenderWindow& window) {
	for (int i = 0; i != width; ++i) {
		for (int j = 0; j != height; ++j) {
			window.draw(pixels[i + j * width]);
		}
	}
}

bool RasterScreen::pixel_on_screen(int w, int h) {
		return (((w >= 0) && (w < width)) && ((h >= 0) && (h < height)));
}

void RasterScreen::clear() {
		for (int i = 0; i != width; ++i) {
				for (int j = 0; j != height; ++j) {
						pixels[i + j * width].setFillColor(sf::Color::White);
				}
		}
		z_buffer = std::vector<float>(width * height, -1);
}

int RasterScreen::get_width() {
		return width;
}

int RasterScreen::get_height() {
		return height;
}

int RasterScreen::trim_width(int w) {
	if (w > up_boarder) {
		w = up_boarder;
	}
	else if (w < down_boarder) {
		w = down_boarder;
	}
	return w;
}

int RasterScreen::trim_height(int h) {
  if (h > up_boarder) {
		h = up_boarder;
	}
	else if (h < down_boarder) {
		h = down_boarder;
	}
	return h;
}

}//namespace Sanches_project
