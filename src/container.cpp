#include "pch.h"
#include "container.h"

bool Container::equal(const Shape &s1, const Shape &s2) {
	Line* l, *l2;
	Circle * c1, * c2;
	Point A_A2, A_B2;
	switch (s1.type) {
		case Shape::shapeType::Line:
			if (s2.type != Shape::shapeType::Line) return false; // not Line::Line
			l = (Line*)&s1; l2 = (Line*)&s2;
			if (l2->k != l->k || l->b != l2->b || (l2->vertical ^ l->vertical) ||
				 (l2->vertical && l->vertical && l->vertical_x != l2->vertical_x))
				return false;
			if (l->lineType == Line::LineType::Line || 
					l2->lineType == Line::LineType::Line) {
				l2 = (Line*)&s2;
				return (l->vertical && l2->vertical && l->vertical_x == l2->vertical_x ||
					!l->vertical && !l2->vertical && l2->k == l->k && l->b == l2->b);
			}
			if (l2->lineType == Line::LineType::Segment &&
					l->lineType == Line::LineType::Segment) {
				int d1 = (int) abs(l->A.x - l->B.x);
				int d2 = (int) abs(l2->A.x - l2->B.x);
				if (d1 > d2) {		// little front
					auto tmp = l2;
					l2 = l;
					l = tmp;
				}
				if (l->A.x < l2->B.x && l->A.x > l2->A.x || l->B.x < l2->B.x && l->B.x > l2->A.x ||
					l->A.x == l2->A.x || l->B.x == l2->B.x) return true;
				else if (l->A.x == l->B.x && (l->A.y < l2->B.y && l->A.y > l2->A.y ||
					l->B.y < l2->B.y && l->B.y > l2->A.y ||
					l->A.y == l2->A.y || l->B.y == l2->B.y)) return true;
				return false;
			}
			if (l2->lineType == Line::LineType::Ray) {// put ray on No.1
				auto tmp = l2;
				l2 = l;
				l = tmp;
			}
			if (l2->lineType == Line::LineType::Ray && l->lineType == Line::LineType::Ray) {
				if (l2->V.pointMul(l->V) > 0) return true;
				Point p = l->oA.sub(l2->oA);
				if (p.x == 0 && p.y == 0 || p.pointMul(l->V) > 0) return false;
				return true;
			}
			A_A2 = l2->A.sub(l->oA), A_B2 = l2->B.sub(l->oA);
			if (A_A2.pointMul(l->V) > 0 || A_B2.pointMul(l->V) > 0) return true;
			return false;
			break;
		case Shape::shapeType::Circle:
			if (s2.type != Shape::shapeType::Circle) return false;
			c1 = (Circle*)&s1; c2 = (Circle*)&s2;
			return (c1->P.equal(c2->P) && c1->r == c2->r);
			break;
		default:
			return false;
			break;
	}
}

Shape* Container::find(const Shape &shape) {
	double hash = myHashFunc(shape);
	auto pr = map.equal_range(hash);
	while (pr.first != pr.second) {
		// check if equal
		Line *l = (Line*)&(pr.first->second);
		if (equal(*pr.first->second, shape)) {
			return pr.first->second;
		}
		++pr.first;
	}
	Shape *ret = new Shape();
	ret->valid = false;
	return ret;
}

bool Container::insert(Shape &shape) {
	Line* lp = (Line*)&shape;
	if (find(shape)->valid) {
		throw invalid_argument("already exsist!");
		// exception TODO
	} else {
		map.insert({ myHashFunc(shape), &shape });
		if (shape.type == Shape::shapeType::Line) {
			Line *l = (Line*)&shape;
			lineVec.push_back(l);
		} else {
			circleVec.push_back((Circle*)&shape);
		}
	}
	return false;
}
