#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen.cpp"
#include "renderer.cpp"

int main()
{
	int w, h, cont;
	/*
	std::cout << "Would you like to continue?\n";
	std::cin >> cont;
	while (cont) {
		std::cout << "Print width and height\n";
		std::cin >> w >> h;
		sf::RenderWindow window(sf::VideoMode(w, h), "It works!");
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			//window.clear(sf::Color(250, 220, 100, 0));
			window.display();
		}
		std::cout << "Would you like to continue?\n";
		std::cin >> cont;
	}
	*/
	/*
	std::cin >> w >> h;
	RasterScreen screen(w, h);
	while (screen.isOpen()) {
		sf::Event event;
		while (screen._window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				screen._window.close();
			}
		}
		screen.draw();
	}
	*/
	std::cout << "Print width and height\n";
	std::cin >> w >> h;
	RasterScreen screen(w, h);
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