#pragma once

#include "screen.h"
#include "figures.h"

namespace Sanches_project {

class Renderer {
public:

	void draw(const Triangle& source, RasterScreen* screen);

private:

	RasterTriangle discrete(const Triangle& source);

	void triangle_sort(RasterTriangle& source);

	void fast_rasterisation_cache(RasterScreen* screen, RasterPoint p1, RasterPoint p2,
		std::vector<RasterPoint>& board, sf::Color color);

	void fast_rasterisation(RasterScreen* screen, RasterPoint p1, RasterPoint p2, sf::Color color);

	void triangle_rasterisation(RasterScreen* screen, RasterTriangle source, sf::Color color);

	bool is_point_on_screen(RasterScreen* screen, RasterPoint source);

	bool is_triangle_on_screen(RasterScreen* screen, RasterTriangle source);
};

}//namespace Sanches_project
