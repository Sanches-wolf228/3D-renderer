#include "renderer.h"
#include <cmath>
#include <cassert>

namespace Sanches_project {

void Renderer::draw(Triangle& source) {
		for (int i = 0; i != 3; ++i) {
				source.vertices[i].coordinates = camera->camera_view_matrix * source.vertices[i].coordinates;
		}
		std::vector<Triangle> targets;
		clipping(source, targets);
		for (Triangle triangle : targets) {
				transfer_to_screen(triangle);
				triangle_rasterisation(discrete(triangle), source.color);
		}
}

RasterTriangle Renderer::discrete(const Triangle& source) {
	RasterTriangle answer;
	for (int i = 0; i != 3; ++i) {
		answer.vertices[i].x = (int)std::round(source.vertices[i].coordinates[0] * screen->width);
		answer.vertices[i].y = (int)std::round(source.vertices[i].coordinates[1] * screen->height);
		answer.vertices[i].z = std::round(source.vertices[i].coordinates[2]);
	}
	return answer;
}

void Renderer::clipping(Triangle& source, std::vector<Triangle>& targets) {
		assert(targets.size() == 0);
		targets.push_back(source);
		// будет добавлена обрезка по граням near и far
}

void Renderer::triangle_sort(RasterTriangle& source) {
	// сортируем точки в треугольнике по возрастанию значений координаты x
	RasterPoint buffer{};
	for (int i = 1; i != 3; ++i) {
		if (source.vertices[i].x < source.vertices[0].x) {
			buffer = source.vertices[0];
			source.vertices[0] = source.vertices[i];
			source.vertices[i] = buffer;
		}
	}
	if (source.vertices[2].x < source.vertices[1].x) {
		buffer = source.vertices[1];
		source.vertices[1] = source.vertices[2];
		source.vertices[2] = buffer;
	}
	// переписать, используя std::swap
}

void Renderer::fast_rasterisation(RasterPoint p1, RasterPoint p2, sf::Color color) {
	assert(p1.x = p2.x);

	int x = p1.x;

	if (p1.y == p2.y) {
			screen->pick_pixel(x, p1.y, p1.z, color);
			screen->pick_pixel(x, p2.y, p2.z, color);
			return;
	}

	if (p2.y < p1.y) {
			std::swap(p1, p2);
	}

	if ((p1.y >= screen->height) || (p2.y < 0)) {
			return;
	}

	double dz = (p2.z - p1.z) / (p2.y - p1.y);

	if (p1.y < 0) {
			p1.z -= p1.y * dz;
			p1.y = 0;
	}

	if (p2.y >= screen->height) {
			p2.z -= (p2.y - screen->height + 1) * dz;
			p2.y = screen->height;
	}

	double z = p1.z;

	for (int y = p1.y; y != p2.y; ++y) {
		screen->pick_pixel(x, y, z, color);
		z += dz;
	}
	return;
}


void Renderer::triangle_rasterisation(RasterTriangle source, sf::Color color) {
	triangle_sort(source);

	RasterPoint left = source.vertices[0];
	RasterPoint mid = source.vertices[1];
	RasterPoint right = source.vertices[2];

	if ((left.x >= screen->width) || (right.x < 0)) {
			return;
	}

	RasterPoint buf1, buf2;

	for (int column = std::max(0, left.x); column != std::min(mid.x, screen->width); ++column) {
			buf1.x = column;
			buf1.y = height_calculate(left, mid, buf1.x);
			buf1.z = depth_calculate(left, mid, buf1.x, buf1.y);

			buf2.x = column;
			buf2.y = height_calculate(left, right, buf2.x);
			buf2.z = depth_calculate(left, right, buf2.x, buf2.y);

			fast_rasterisation(buf1, buf2, color);
	}

	for (int column = std::min(mid.x, screen->width - 1); column != std::min(right.x, screen->width); ++column) {
			buf1.x = column;
			buf1.y = height_calculate(mid, right, buf1.x);
			buf1.z = depth_calculate(mid, right, buf1.x, buf1.y);

			buf2.x = column;
			buf2.y = height_calculate(left, right, buf2.x);
			buf2.z = depth_calculate(left, right, buf2.x, buf2.y);

			fast_rasterisation(buf1, buf2, color);
	}
	return;
}

int height_calculate(const RasterPoint& p1, const RasterPoint& p2, int x) {
		assert(p1.x != p2.x); // not a vertical line
		assert((p1.x - x) * (p2.x - x) <= 0); // x coordinate is inside segment

		float y, alpha, betta; // y = alpha * x + betta

		alpha = ((float)(p2.y - p1.y)) / (p2.x - p1.x);
		betta = ((float)(p1.y * p2.x - p2.y * p1.x)) / (p2.x - p1.x);

		y = std::round(alpha * x + betta);

		return (int)y;
}

float Renderer::depth_calculate(const RasterPoint& p1, const RasterPoint& p2, int x, int y) {
		assert((p1.x - x) * (p2.x - x) <= 0); // x coordinate is inside segment
		assert((p1.y - y) * (p2.y - y) <= 0); // y coordinate is inside segment
		float answer = p1.z * (abs(x - p2.x) + abs(y - p2.y)) + p2.z * (abs(x - p1.x) + abs(y - p1.y));
		answer /= (abs(p1.x - p2.x) + abs(p1.y - p2.y));
		return answer;
}

void Renderer::transfer_to_screen(Triangle& triangle) {
		for (int i = 0; i != 3; ++i) {
				assert(triangle.vertices[i].coordinates[3] != 0);
				triangle.vertices[i].coordinates = camera->perspective_matrix * triangle.vertices[i].coordinates;
				for (int j = 0; j != 4; ++j) {
						triangle.vertices[i].coordinates[j] /= triangle.vertices[i].coordinates[3];
				}

		}
		
}
}//namespace Sanches_project

