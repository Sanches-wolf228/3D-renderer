#pragma once

#include "screen.cpp"
#include "figures.cpp"

class Renderer {
public:

	void segment_rasterisation(RasterScreen *screen, Segment source, sf::Color color) {
		int x0 = round(source.ends[0].coordinates[0]);
		int y0 = round(source.ends[0].coordinates[1]);
		int x1 = round(source.ends[1].coordinates[0]);
		int y1 = round(source.ends[1].coordinates[1]);
		double z0 = source.ends[0].coordinates[2];
		double z1 = source.ends[1].coordinates[2];

		if (z0 < 0 && z1 < 0) {
			return;
		}

		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;

		if (z0 < 0) {
			double buf = (x0 * z1 - x1 * z0) / (z1 - z0);
			if (sx == 1) {
				x0 = ceil(buf);
			}
			else if (sx == -1) {
				x0 = floor(buf);
			}
			buf = (y0 * z1 - y1 * z0) / (z1 - z0);
			if (sy == 1) {
				y0 = ceil(buf);
			}
			else if (sy == -1) {
				y0 = floor(buf);
			}
		}
		else if (z1 < 0) {
			double buf = (x0 * z1 - x1 * z0) / (z1 - z0);
			if (sx == -1) {
				x1 = ceil(buf);
			}
			else if (sx == 1) {
				x1 = floor(buf);
			}
			buf = (y0 * z1 - y1 * z0) / (z1 - z0);
			if (sy == -1) {
				y1 = ceil(buf);
			}
			else if (sy == 1) {
				y1 = floor(buf);
			}
		}

		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);

		if (dx == 0 && dy == 0) {
			if (screen->z_buffer[x0][y0] == -1) {
				screen->_pixels[x0][y0].setFillColor(color);
			}
			else if (z0 <= screen->z_buffer[x0][y0] || z1 <= screen->z_buffer[x0][y0]) {
				screen->_pixels[x0][y0].setFillColor(color);
			}
			return;
		}

		int err = dx - dy;

		int x = x0;
		int y = y0;
		double z;
		double length = sqrt(double(dx * dx + dy * dy));

		while (!((x == x1) && (y == y1))) {
			int e2 = err * 2;
			if (e2 >= -dy) {
				err -= dy;
				x += sx;
			}
			if (e2 < dx) {
				err += dx;
				y += sy;
			}
			z = z0 + (z1 - z0) * sqrt(double((x - x0) * (x - x0) + (y - y0) * (y - y0))) / length;
			screen->pick_pixel(x, y, z, color);
		}
		return;
	}
};
