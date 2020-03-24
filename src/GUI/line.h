#pragma once
#include <iostream>
#include "point.h"
#include "shape.h"

class Line : public Shape {
public:
	Point A, B, V, oA, oB;
	double k = 0, b = 0, vertical_x = 0;
	bool vertical = false;

	enum class LineType { Line, Ray, Segment };
	LineType lineType = LineType::Line;

	Line();
	Line(int x1, int y1, int x2, int y2, LineType t);
	void show();
	Point getCross(Line* l2);
	Point setX(double x);
	Point setY(double y);
	void printData(ofstream& ofs);
};