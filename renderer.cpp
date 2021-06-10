#include "renderer.h"
#include <cmath>
#include <cassert>

namespace Sanches_project {

void Renderer::draw(Triangle source) {
		for (int i = 0; i != 3; ++i) {
				camera->change_view(source.vertices[i].coordinates);
		}
		std::vector<Triangle> targets;
		clipping(source, targets);
		for (Triangle triangle : targets) {
				transfer_to_screen(triangle);
				triangle_rasterisation(discrete(triangle), source.color);
		}
}

void Renderer::set_parameters(RasterScreen* screen, Camera* camera) {
		this->camera = camera;
		this->screen = screen;
}

RasterTriangle Renderer::discrete(const Triangle& source) {
	RasterTriangle answer;
	for (int i = 0; i != 3; ++i) {
		answer.vertices[i].x = (int)std::round(source.vertices[i].coordinates[0] * screen->get_width());
		answer.vertices[i].y = (int)std::round(source.vertices[i].coordinates[1] * screen->get_height());
		answer.vertices[i].z = std::round(source.vertices[i].coordinates[2]);
	}
	return answer;
}

void Renderer::clipping(Triangle& source, std::vector<Triangle>& targets) {
		assert(targets.size() == 0);
		depth_sort(source);
		if ((source.vertices[0].coordinates[2] >= camera->far()) ||
				(source.vertices[2].coordinates[2] <= camera->near())) {
				return;
		}
		
		std::vector<Triangle> near_clipped;

		if (source.vertices[0].coordinates[2] >= camera->near()) {
				near_clipped.push_back(source);
		}
		else if (source.vertices[1].coordinates[2] >= camera->near()) {
				Point p1 = cross_point(source.vertices[0], source.vertices[1], camera->near());
				Point p2 = cross_point(source.vertices[0], source.vertices[2], camera->near());
				near_clipped.push_back(Triangle{ { source.vertices[2], p1, p2 }, source.color });
				near_clipped.push_back(Triangle{ { source.vertices[2], p1, source.vertices[1] }, source.color });
		}
		else {
				Point p1 = cross_point(source.vertices[0], source.vertices[2], camera->near());
				Point p2 = cross_point(source.vertices[1], source.vertices[2], camera->near());
				near_clipped.push_back(Triangle{ { source.vertices[2], p1, p2 }, source.color });
		}
		
		for (Triangle triangle : near_clipped) {
				depth_sort(triangle);
				if (triangle.vertices[2].coordinates[2] <= camera->far()) {
						targets.push_back(triangle);
				}
				else if (source.vertices[1].coordinates[2] <= camera->far()) {
						Point p1 = cross_point(source.vertices[0], source.vertices[2], camera->far());
						Point p2 = cross_point(source.vertices[1], source.vertices[2], camera->far());
						targets.push_back(Triangle{ { source.vertices[0], p1, p2 }, source.color });
						targets.push_back(Triangle{ { source.vertices[0], p2, source.vertices[1] }, source.color });
				}
				else {
						Point p1 = cross_point(source.vertices[0], source.vertices[1], camera->far());
						Point p2 = cross_point(source.vertices[0], source.vertices[2], camera->far());
						targets.push_back(Triangle{ { source.vertices[0], p1, p2 }, source.color });
				}
		}
		return;
}

void Renderer::triangle_sort(RasterTriangle& source) {
	// sort the points in ascending order of the X coordinate
	for (int i = 1; i != 3; ++i) {
		if (source.vertices[i].x < source.vertices[0].x) {
				std::swap(source.vertices[0], source.vertices[i]);
		}
	}
	if (source.vertices[2].x < source.vertices[1].x) {
			std::swap(source.vertices[1], source.vertices[2]);
	}
}

void Renderer::depth_sort(Triangle& source) {
		// sort the points in ascending order of the Z coordinate
		for (int i = 1; i != 3; ++i) {
				if (source.vertices[i].coordinates[2] < source.vertices[0].coordinates[2]) {
						std::swap(source.vertices[0], source.vertices[i]);
				}
		}
		if (source.vertices[2].coordinates[2] < source.vertices[1].coordinates[2]) {
				std::swap(source.vertices[1], source.vertices[2]);
		}
}

void Renderer::fast_rasterisation(RasterPoint p1, RasterPoint p2, sf::Color color) {
	assert(p1.x == p2.x);

	int x = p1.x;

	if (p2.y < p1.y) {
			std::swap(p1, p2);
	}

	if ((p1.y >= screen->get_height()) || (p2.y < 0)) {
			return;
	}

	if (p1.y == p2.y) {
			screen->pick_pixel(x, p1.y, p1.z, color);
			screen->pick_pixel(x, p2.y, p2.z, color);
			return;
	}

float dz = (p2.z - p1.z) / (p2.y - p1.y);

	if (p1.y < 0) {
			p1.z -= p1.y * dz;
			p1.y = 0;
	}

	if (p2.y >= screen->get_height()) {
			p2.z -= (p2.y - screen->get_height() + 1) * dz;
			p2.y = screen->get_height();
	}
	
	float z = p1.z;

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

	if ((left.x >= screen->get_width()) || (right.x < 0)) {
			return;
	}

	RasterPoint buf1, buf2;

	if (mid.x >= 0) {
			for (int column = std::max(0, left.x); column != std::min(mid.x, screen->get_width()); ++column) {
					buf1.x = column;
					buf1.y = height_calculate(left, mid, buf1.x);
					buf1.z = depth_calculate(left, mid, buf1.x, buf1.y);

					buf2.x = column;
					buf2.y = height_calculate(left, right, buf2.x);
					buf2.z = depth_calculate(left, right, buf2.x, buf2.y);

					fast_rasterisation(buf1, buf2, color);
			}
	}

	if (mid.x <= screen->get_width() - 1) {
			for (int column = std::max(0, mid.x); column != std::min(right.x, screen->get_width()); ++column) {
					buf1.x = column;
					buf1.y = height_calculate(mid, right, buf1.x);
					buf1.z = depth_calculate(mid, right, buf1.x, buf1.y);

					buf2.x = column;
					buf2.y = height_calculate(left, right, buf2.x);
					buf2.z = depth_calculate(left, right, buf2.x, buf2.y);

					fast_rasterisation(buf1, buf2, color);
			}
	}

	return;
}

int Renderer::height_calculate(const RasterPoint& p1, const RasterPoint& p2, int x) {
		assert(p1.x != p2.x); // not a vertical line
		assert(((p1.x <= x) && (x <= p2.x)) || ((p2.x <= x) && (x <= p1.x))); // x coordinate is inside segment

		float y, alpha, betta; // y = alpha * x + betta

		alpha = ((float)(p2.y - p1.y)) / (p2.x - p1.x);
		betta = ((float)(p1.y * p2.x - p2.y * p1.x)) / (p2.x - p1.x);

		y = std::round(alpha * x + betta);

		return (int)y;
}

float Renderer::depth_calculate(const RasterPoint& p1, const RasterPoint& p2, int x, int y) {
		assert(((p1.x <= x) && (x <= p2.x)) || ((p2.x <= x) && (x <= p1.x))); // x coordinate is inside segment
		assert(((p1.y <= y) && (y <= p2.y)) || ((p2.y <= y) && (y <= p1.y))); // y coordinate is inside segment
		float answer = p1.z * (abs(x - p2.x) + abs(y - p2.y)) + p2.z * (abs(x - p1.x) + abs(y - p1.y));
		answer /= (abs(p1.x - p2.x) + abs(p1.y - p2.y));
		return answer;
}

void Renderer::transfer_to_screen(Triangle& triangle) {
		for (int i = 0; i != 3; ++i) {
				assert(triangle.vertices[i].coordinates[3] != 0);
				camera->set_perspective(triangle.vertices[i].coordinates);
				camera->set_to_screen(triangle.vertices[i].coordinates);
				for (int j = 0; j != 4; ++j) {
						triangle.vertices[i].coordinates[j] /= triangle.vertices[i].coordinates[3];
				}
		}
}

Point Renderer::cross_point(const Point& p1, const Point& p2, float z) {
		assert(((p1.coordinates[2] <= z) && (z <= p2.coordinates[2]))
				|| ((p2.coordinates[2] <= z) && (z <= p1.coordinates[2]))); // z coordinate is inside segment

		if (p1.coordinates[2] == p2.coordinates[2]) {
				return p1;
		}

		Point answer;

		answer.coordinates = { 0, 0, z, 1 };

		float alpha, betta; // x = alpha * z + betta

		alpha = ((float)(p2.coordinates[0] - p1.coordinates[0])) / (p2.coordinates[2] - p1.coordinates[2]);
		betta = ((float)(p1.coordinates[0] * p2.coordinates[2] - p2.coordinates[0] * p1.coordinates[2])) / (p2.coordinates[2] - p1.coordinates[2]);

		answer.coordinates[0] = (alpha * z + betta);

		// y = alpha * z + betta

		alpha = ((float)(p2.coordinates[1] - p1.coordinates[1])) / (p2.coordinates[2] - p1.coordinates[2]);
		betta = ((float)(p1.coordinates[1] * p2.coordinates[2] - p2.coordinates[1] * p1.coordinates[2])) / (p2.coordinates[2] - p1.coordinates[2]);

		answer.coordinates[1] = (alpha * z + betta);

		return answer;
}

}//namespace Sanches_project

