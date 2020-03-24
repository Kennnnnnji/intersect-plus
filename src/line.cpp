#include "pch.h"
#include "line.h"

Line::Line() {}

Line::Line(int x1, int y1, int x2, int y2, LineType t) {
	type = shapeType::Line;
	lineType = t;
	A = Point(x1, y1);
	B = Point(x2, y2);
	V = B.sub(A);
	oA = A, oB = B;
	// x, y little front
	if (x1 > x2 || x1 == x2 && y1 > y2) {
		auto tmp = A;
		A = B;
		B = tmp;
	}
	if (x1 == x2) {
		vertical = true;
		vertical_x = (double)x1;
	} else {
		k = ((double)y1 - (double)y2) / ((double)x1 - (double)x2);
		b = (double)y1 - (double)k * (double)x1;
	}
}

void Line::show() {
	using namespace std;
	cout << k << " " << b << endl;
}

Point Line::getCross(Line* l2) {
	// parallel
	if (vertical && l2->vertical || 
		(!vertical && !l2->vertical && this->k == l2->k)) {
		return Point();
	}
	// cross
	Point p;
	if (vertical) {
		p =  l2->setX(vertical_x);
	} else if (l2->vertical) {
		p = setX(vertical_x);
	}
	double x = (b - l2->b) / (l2->k - k);
	p = Point(x, k * x + b);
	Point p2 = p.sub(oA);
	switch (this->lineType)
	{
	case LineType::Ray:
		p.valid = p2.pointMul(V) >= 0;
		break;
	case Line::LineType::Line: 
		p.valid = true;
		break;
	case LineType::Segment:
		p.valid = p.x >= A.x && p.x <= B.x && 
			(p.y >= A.y && p.y <= B.y || p.y >= B.y && p.y <= A.y);
		break;
	default:
		p.valid = false;
		break;
	}
	if (p.valid) {
		Point p2 = p.sub(l2->oA);
		switch (l2->lineType) 
		{
		case LineType::Line:
			p.valid = true;
			break;
		case LineType::Ray:
			p.valid = p2.pointMul(l2->V) >= 0;
			break;
		case LineType::Segment:
			p.valid = p.x >= A.x && p.x <= B.x && 
				(p.y >= A.y && p.y <= B.y || p.y >= B.y && p.y <= A.y);
			break;
		default:
			p.valid = false;
			break;
		}
	}
	return p;
}

Point Line::setX(double x) {
	if (vertical) {
		std::cerr << "vertical in setX()" << std::endl;
	}
	return Point(x, k * x + b);
}
