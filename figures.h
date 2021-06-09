#pragma once
#include <SFML/Graphics.hpp>
#include <glm.hpp>

namespace Sanches_project {

struct Point {
	glm::vec4 coordinates;
};

struct RasterPoint {
	int x;
	int y;
	float z;
};

struct RasterTriangle {
	RasterPoint vertices[3];
};

struct Triangle {
	Point vertices[3];
	sf::Color color;
};

}//namespace Sanches_project