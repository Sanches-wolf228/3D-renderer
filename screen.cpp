#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Renderer;

class RasterScreen {
private:
	
	int _width;
	int _height;
	std::vector<std::vector<sf::RectangleShape>> _pixels;
	std::vector<std::vector<double>> z_buffer;

	void pick_pixel(int width, int height, double depth, sf::Color color) {
		if (z_buffer[width][height] == -1 || depth <= z_buffer[width][height]) {
			_pixels[width][height].setFillColor(color);
		}
		return;
	}

public:
	sf::RenderWindow _window;
	RasterScreen() = delete;
	RasterScreen(int width, int height) : _width(width), _height(height) {
		if (_width > 1000) {
			_width = 1000;
		}
		else if (_width < 120) {
			_width = 120;
		}
		if (_height > 1000) {
			_height = 1000;
		}
		else if (_height < 70) {
			_height = 70;
		}

		_pixels = std::vector<std::vector<sf::RectangleShape>>(_width,
			std::vector<sf::RectangleShape>(_height));
		z_buffer = std::vector<std::vector<double>>(_width, std::vector<double> (_height, -1));
		_window.create(sf::VideoMode(_width, _height), "It works!");
		//_window.setVerticalSyncEnabled(true);

		for (int i = 0; i != _width; ++i) {
			for (int j = 0; j != _height; ++j) {
				_pixels[i][j].setSize(sf::Vector2f(1, 1));
				_pixels[i][j].setPosition(i, j);
			}
		}
	}

	void set_pixels() {
		for (int i = 0; i != _width; ++i) {
			for (int j = 0; j != _height; ++j) {
				_pixels[i][j].setFillColor(sf::Color(i * i, i - 2 * j * i, j * j * j - i * i));
			}
		}
	}

	void draw() {
		for (int i = 0; i != _width; ++i) {
			for (int j = 0; j != _height; ++j) {
				_window.draw(_pixels[i][j]);
			}
		}
		_window.display();
	}

	bool isOpen() {
		return _window.isOpen();
	}

	friend class Renderer;
};