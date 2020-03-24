#pragma once
#include <unordered_map>
#include "shape.h"
#include "line.h"
#include "circle.h"

#include <vector>

using namespace std;

class Container {
private:
	int id;
	string name;

public:
	unordered_multimap<double, Shape*> map;
	vector<Line*> lineVec;
	vector<Circle*> circleVec;
	bool equal(const Shape &s1, const Shape &s2);
	Shape* find(const Shape &shape);
	bool insert(Shape &shape);

	double myHashFunc(const Shape &obj) {
		double val = 0;
		Line* l;
		switch (obj.type) {
			case Shape::shapeType::Line:
				l = (Line*)&obj;
				val = 0 + l->k + ((Line*)&obj)->b;
				break;
			case Shape::shapeType::Ray:
				// same as line
				val = 0 + ((Line*)&obj)->k + ((Line*)&obj)->b;
				break;
				// TODO
			default:
				break;
		}
		//return hash<double>()(val);
		return val;
	}
};

