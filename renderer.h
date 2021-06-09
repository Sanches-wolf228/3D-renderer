#pragma once

#include "screen.h"
#include "figures.h"
#include "camera.h"

namespace Sanches_project {

class Renderer {
public:

	void draw(Triangle& source);

private:

		RasterScreen* screen;

		Camera* camera;

		RasterTriangle discrete(const Triangle& source);

		void clipping(Triangle& source, std::vector<Triangle>& target);

		void triangle_sort(RasterTriangle& source);

		void fast_rasterisation(RasterPoint p1, RasterPoint p2, sf::Color color);

		void triangle_rasterisation(RasterTriangle source, sf::Color color);

		int height_calculate(const RasterPoint& p1, const RasterPoint& p2, int x);

		float depth_calculate(const RasterPoint& p1, const RasterPoint& p2, int x, int y);

		void transfer_to_screen(Triangle& triangle);
};

}//namespace Sanches_project
