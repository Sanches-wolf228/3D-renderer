#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen.cpp"
#include "renderer.cpp"

int main()
{
	int w, h, cont;
	
	std::cout << "Would you like to begin? (1 - yes, 0 - no)\n";
	std::cin >> cont;
	if (!cont) {
		return 0;
	}
	while (cont) {
		std::cout << "Print width and height\n";
		std::cin >> w >> h;
		RasterScreen screen(w, h);
		screen.set_pixels();
		while (screen.isOpen()) {
			sf::Event event;
			while (screen._window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					screen._window.close();
				}
			}
			screen.draw();
		}
		std::cout << "Would you like to draw another frame? (1 - yes, 0 - no)\n";
		std::cin >> cont;
	}

	std::cout << "Drawing lines test (1 - yes, 0 - no)\n";
	std::cin >> cont;
	if (!cont) {
		return 0;
	}
	std::cout << "Print width and height of frame\n";
	std::cin >> w >> h;
	RasterScreen screen(w, h);
	std::cout << "Type leftarrow to draw a line on the screen\n";
	std::cout << "Do not enter x or y values, that are out of the screen\n";
	while (screen.isOpen()) {
		sf::Event event;
		while (screen._window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				screen._window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					Point a1, a2;
					std::cout << "First point coordinates\n";
					std::cin >> a1.coordinates[0] >> a1.coordinates[1] >> a1.coordinates[2];
					std::cout << "Second point coordinates\n";
					std::cin >> a2.coordinates[0] >> a2.coordinates[1] >> a2.coordinates[2];
					Segment x(a1, a2);
					Renderer render;
					int red, green, blue;
					std::cout << "Choose color\n";
					std::cin >> red >> green >> blue;
					sf::Color color(red, green, blue);
					render.segment_rasterisation(&screen, x, color);
				}
			}
		}
		screen.draw();
	}
	return 0;
}