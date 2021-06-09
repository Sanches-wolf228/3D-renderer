#pragma once

#include "screen.h"
#include "figures.h"
#include "camera.h"

namespace Sanches_project {

class Renderer {
public:

	void draw(Triangle& source, RasterScreen* screen, Camera camera);

private:

	RasterTriangle discrete(const Triangle& source, RasterScreen* screen);

	void clipping(Triangle& source, Camera camera, std::vector<Triangle>& target);

	void triangle_sort(RasterTriangle& source);

	/**/void fast_rasterisation_cache(RasterScreen* screen, RasterPoint p1, RasterPoint p2,
		std::vector<RasterPoint>& board, sf::Color color);

	void fast_rasterisation(RasterScreen* screen, RasterPoint p1, RasterPoint p2, sf::Color color);

	void triangle_rasterisation(RasterScreen* screen, RasterTriangle source, sf::Color color);

	/**/bool is_point_on_screen(RasterScreen* screen, RasterPoint source);

	/**/bool is_triangle_on_screen(RasterScreen* screen, RasterTriangle source);

	double depth_calculate(const RasterPoint &p1, const RasterPoint &p2, int x, int y);
};

}//namespace Sanches_project
