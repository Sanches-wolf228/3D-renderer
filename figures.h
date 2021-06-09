#pragma once
#include <SFML/Graphics.hpp>

namespace Sanches_project {

struct Point {
	double coordinates[3];
};

struct RasterPoint {
	int x;
	int y;
	double z;
};

struct RasterTriangle {
	RasterPoint vertices[3];
};

struct Triangle {
	Point vertices[3];
	sf::Color color;
};

}//namespace Sanches_project