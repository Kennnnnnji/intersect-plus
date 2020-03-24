#pragma once
#include "point.h"
#include "line.h"
#include "shape.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <fstream>

class Circle : public Shape {
public:
	Point P;
	double r;
	Circle() {};
    Circle(Point P, double r) {
		type = shapeType::Circle;
        this->P = P;
        this->r = r;
    }
	double getDistanceLine(Line l) {
		if (l.vertical) return abs(P.x - l.vertical_x);
		return abs(-l.k * P.x + P.y - l.b)/sqrt(l.k * l.k + 1);
	}
	bool isCross(Line l) {
		return getDistanceLine(l) <= r;
	}
	bool isCross(Circle c2) {
		double distance = P.getDistance(c2.P);
		return distance <= r + c2.r && distance >= abs(r - c2.r);
	}
	void printData(ofstream& ofs) {
		ofs << "C " << P.x << " " << P.y << " " << r << endl;
	}
	pointPair intersections(Circle* c) {
		if (!isCross(*c)) return pointPair(Point(), Point());
		Point P0((double)P.x, (double)P.y);
		Point P1((double)c->P.x, (double)c->P.y);
		double d, a, h;
		d = P0.getDistance(P1);
		a = ((double)r * r - (double)c->r * c->r + (double)d * d) / (2 * (double)d);
		h = sqrt((double)r * r - (double)a * a);
		Point P2 = P1.sub(P0).scale(a / d).add(P0);
		double x3, y3, x4, y4;
		x3 = (double)P2.x + (double)h * (P1.y - P0.y) / d;
		y3 = (double)P2.y - (double)h * (P1.x - P0.x) / d;
		x4 = (double)P2.x - (double)h * (P1.y - P0.y) / d;
		y4 = (double)P2.y + (double)h * (P1.x - P0.x) / d;
		return pointPair(Point(x3, y3), Point(x4, y4));
	}
};

static pointPair getCrossPoints(Circle* cir, Line* l) {
	if (!cir->isCross(*l)) {
		return pointPair(Point(), Point());
	}
	double k = l->k, b = l->b;
	double cx = cir->P.x, cy = cir->P.y, r = cir->r;
	Point p3;
	if (l->vertical) {
		// TODO wrong
		double delta = r * r - (l->vertical_x - cx) * (l->vertical_x - cx);
		delta = sqrt(delta);
		double x1 = l->vertical_x;
		Point p1(x1, cir->P.y + delta); 
		Point p2(x1, cir->P.y - delta);
		
		switch (l->lineType)
		{
		case Line::LineType::Line:
			p1.valid = true;
			p2.valid = true;
			break;
		case Line::LineType::Ray:
			p3 = p1.sub(l->oA);
			p1.valid = p3.pointMul(l->V) >= 0;
			p3 = p2.sub(l->oA);
			p2.valid = p3.pointMul(l->V) >= 0;
			break;
		case Line::LineType::Segment:
			p1.valid = p1.x >= l->A.x && p1.x <= l->B.x && p1.y >= l->A.y && p1.y <= l->B.y;
			p2.valid = p2.x >= l->A.x && p2.x <= l->B.x && p2.y >= l->A.y && p2.y <= l->B.y;
			break;
		default:
			p1.valid = p2.valid = false;
			break;
		}
		return pointPair(p1, p2);
	}

	double P = cx * cx + (b - cy) * (b - cy) - r * r;
	double a = (1 + k * k);
	double b1 = (2 * cx - 2 * k * (b - cy));
	double c1 = sqrt(b1 * b1 - 4 * a * P);
	double x1, y1, x2, y2;
	x1 = ((double)b1 + c1) / (2 * a);
	y1 = k * x1 + b;
	x2 = ((double)b1 - c1) / (2 * a);
	y2 = k * x2 + b;
	Point p1(x1, y1);
	Point p2(x2, y2);
	switch (l->lineType)
	{
	case Line::LineType::Line:
		p1.valid = true;
		p2.valid = true;
		break;
	case Line::LineType::Ray:
		p3 = p1.sub(l->oA);
		p1.valid = p3.pointMul(l->V) >= 0;
		p3 = p2.sub(l->oA);
		p2.valid = p3.pointMul(l->V) >= 0;
		break;
	case Line::LineType::Segment:
		p1.valid = x1 >= l->A.x && x1 <= l->B.x && y1 >= l->A.y && y1 <= l->B.y;
		p2.valid = x2 >= l->A.x && x2 <= l->B.x && y2 >= l->A.y && y2 <= l->B.y;
		break;
	default:
		p1.valid = p2.valid = false;
		break;
	}
	return pointPair(p1, p2);
}

