#pragma once

#include <vector>

class Point {
public:
	double coordinates[3];
};

class Segment {
public:
	Point ends[2];
	Segment(Point first, Point second) {
		ends[0] = first;
		ends[1] = second;
	}
};

class Triangle {
public:
	Point vertices[3];
};
