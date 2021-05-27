#include "renderer.h"
#include <cmath>
#include <cassert>

namespace Sanches_project {

RasterTriangle Renderer::discrete(const Triangle& source) {
	RasterTriangle answer;
	for (int i = 0; i != 3; ++i) {
		answer.vertices[i].x = (int)std::round(source.vertices[i].coordinates[0]);
		answer.vertices[i].y = (int)std::round(source.vertices[i].coordinates[1]);
		answer.vertices[i].z = std::round(source.vertices[i].coordinates[2]);
	}
	return answer;
}

void Renderer::draw(const Triangle& source, RasterScreen* screen) {
	triangle_rasterisation(screen, discrete(source), source.color);
}

void Renderer::triangle_sort(RasterTriangle& source) {
	// сортируем точки в треугольнике по возрастанию значений первой координаты
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
}

void Renderer::fast_rasterisation_cache(RasterScreen* screen, RasterPoint p1, RasterPoint p2,
	std::vector<RasterPoint>& board, sf::Color color) {
	assert(is_point_on_screen(screen, p1));
	assert(is_point_on_screen(screen, p2));

	int x0 = p1.x;
	int y0 = p1.y;
	double z0 = p1.z;
	int x1 = p2.x;
	int y1 = p2.y;
	double z1 = p2.z;

	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx == 0 && dy == 0) {
		screen->pick_pixel(x0, y0, z0, color);
		screen->pick_pixel(x0, y0, z1, color);
		return;
	}

	int err = dx - dy;

	int x = x0;
	int y = y0;
	double z = z0;
	double length = sqrt(double(dx * dx + dy * dy));

	int x_shift = (x0 < x1) ? x0 : x1;

	do {
		board[x - x_shift].x = x;
		board[x - x_shift].y = y;
		board[x - x_shift].z = z;

		int e2 = err * 2;
		if (e2 >= -dy) {
			err -= dy;
			x += sx;
		}
		if (e2 < dx) {
			err += dx;
			y += sy;
		}

		z = z0 + (z1 - z0) * sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0)) / length;

		screen->pick_pixel(x, y, z, color);

	} while (!((x == x1) && (y == y1)));
	board[x - x_shift].y = y;
	board[x - x_shift].z = z;
	board[x - x_shift].x = x;
	return;
}

void Renderer::fast_rasterisation(RasterScreen* screen, RasterPoint p1, RasterPoint p2, sf::Color color) {
	assert(is_point_on_screen(screen, p1));
	assert(is_point_on_screen(screen, p2));

	int x = p1.x;
	int y_begin = p1.y;
	double z_begin = p1.z;
	int y_end = p2.y;
	double z_end = p2.z;

	int step = (y_begin < y_end) ? 1 : -1;

	if (y_begin == y_end) {
		screen->pick_pixel(x, y_begin, z_begin, color);
		screen->pick_pixel(x, y_end, z_begin, color);
		return;
	}

	double dz_y = (z_end - z_begin) / abs(y_begin - y_end);

	int y = y_begin;
	double z = z_begin;

	while (y != y_end) {
		y += step;
		z += dz_y;
		screen->pick_pixel(x, y, z, color);
	}
	return;
}

bool Renderer::is_point_on_screen(RasterScreen* screen, RasterPoint source) {
	return screen->pixel_on_screen(source.x, source.y);
}

bool Renderer::is_triangle_on_screen(RasterScreen* screen, RasterTriangle source) {
	for (int i = 0; i != 3; ++i) {
		if (!is_point_on_screen(screen, source.vertices[i])) {
			return false;
		}
	}
	return true;
}

void Renderer::triangle_rasterisation(RasterScreen* screen, RasterTriangle source, sf::Color color) {
	assert(is_triangle_on_screen(screen, source));
	triangle_sort(source);

	RasterPoint left = source.vertices[0];
	RasterPoint mid = source.vertices[1];
	RasterPoint right = source.vertices[2];

	std::vector<RasterPoint> large_part(right.x - left.x + 1);
	std::vector<RasterPoint> first_part(mid.x - left.x + 1);
	std::vector<RasterPoint> second_part(right.x - mid.x + 1);

	if ((mid.y - left.y) * (right.x - left.x) > (right.y - left.y) * (mid.x - left.x)) {
		// центральная точка выше отрезка
		if (left.y < right.y) {
			fast_rasterisation_cache(screen, left, right, large_part, color);
		}
		else {
			fast_rasterisation_cache(screen, right, left, large_part, color);
		}
		if (left.y < mid.y) {
			fast_rasterisation_cache(screen, mid, left, first_part, color);
		}
		else {
			fast_rasterisation_cache(screen, left, mid, first_part, color);
		}
		if (mid.y < right.y) {
			fast_rasterisation_cache(screen, right, mid, second_part, color);
		}
		else {
			fast_rasterisation_cache(screen, mid, right, second_part, color);
		}
	}
	else {
		// центральная точка на отрезке или ниже его
		if (left.y > right.y) {
			fast_rasterisation_cache(screen, left, right, large_part, color);
		}
		else {
			fast_rasterisation_cache(screen, right, left, large_part, color);
		}
		if (left.y > mid.y) {
			fast_rasterisation_cache(screen, mid, left, first_part, color);
		}
		else {
			fast_rasterisation_cache(screen, left, mid, first_part, color);
		}
		if (mid.y > right.y) {
			fast_rasterisation_cache(screen, right, mid, second_part, color);
		}
		else {
			fast_rasterisation_cache(screen, mid, right, second_part, color);
		}
	}

	for (size_t i = 0; i < first_part.size(); ++i) {
		fast_rasterisation(screen, large_part[i], first_part[i], color);
	}

	for (size_t i = 0; i < second_part.size(); ++i) {
		fast_rasterisation(screen, large_part[i + first_part.size() - 1], second_part[i], color);
	}

	return;
}

}//namespace Sanches_project

