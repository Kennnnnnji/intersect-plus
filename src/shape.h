#pragma once
#include "point.h"

class Shape {
public:
	enum class shapeType { Line, Ray, Segment, Circle };
	int index; // to do
	shapeType type;
	bool isLine = false, isCircle = false;
	bool valid = true;
	Shape();
	virtual Point getCross(Shape* shape);
};