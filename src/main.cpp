// Dll1.cpp : 定义 DLL 的导出函数。
//
#include "pch.h"
#include "Dll1.h"
#include <iostream>
#include "shape.h"
#include "line.h"
#include "circle.h"
#include <fstream>
#include "container.h"
#include <sstream>

using namespace std;
// 这是导出函数的一个示例。
unordered_set<Point, myHash>* finalGetCrossPoints(vector<Line*> lineVec, vector<Circle*> circleVec,
	bool debug, bool testPerform) {
	//unordered_set<Point, myHash> pointSet;
	unordered_set<Point, myHash>* pointSet = new unordered_set<Point, myHash>();
	try {
		for (vector<Line*>::iterator iter = lineVec.begin(); iter != lineVec.end(); iter++) {
			for (auto iter2 = iter + 1; iter2 != lineVec.end(); iter2++) {
				Point p = ((Line*)(*iter))->getCross((Line*)*iter2);
				if (p.valid) {
					if (debug) {
						cout << "l & l: ";
						p.show();
					}
					pointSet->insert(p);
				}
			}
		}
		for (vector<Line*>::iterator iter = lineVec.begin(); iter != lineVec.end(); iter++) {
			for (auto iter2 = circleVec.begin(); iter2 != circleVec.end(); iter2++) {
				pointPair pp = getCrossPoints((Circle*)(*iter2), (Line*)(*iter));
				if (pp.first.valid) {
					if (debug) {
						cout << "c & l: ";
						pp.first.show();
					}
					pointSet->insert(pp.first);
				}
				if (pp.second.valid) {
					if (debug) {
						cout << "c & l: ";
						pp.second.show();
					}
					pointSet->insert(pp.second);
				}
			}
		}
		for (auto iter = circleVec.begin(); iter != circleVec.end(); iter++) {
			for (auto iter2 = iter + 1; iter2 != circleVec.end(); iter2++) {
				pointPair pp = ((Circle*)(*iter))->intersections((Circle*)(*iter2));
				if (pp.first.valid) {
					if (debug) {
						cout << "c & c: ";
						pp.first.show();
					}
					pointSet->insert(pp.first);
				}
				if (pp.second.valid) {
					if (debug) {
						cout << "c & c: ";
						pp.second.show();
					}
					pointSet->insert(pp.second);
				}
			}
		}
	} catch (exception& e) {
		cerr << "exception : in insertShape";
		return new unordered_set<Point, myHash>();
	}
	return pointSet;
}
int debug = false, testPerform = false;

bool check_point_overlap(int x1, int y1, int x2, int y2) {
	return x1 == x2 && y1 == y2;
}

void insertShape(ifstream& inFile, char c, Container* container) {
	int x1, y1, x2, y2;
	Line *l;
	Circle *cir;
	switch (c) {
		case 'L':
			inFile >> x1 >> y1 >> x2 >> y2;
			if (check_point_overlap(x1, y1, x2, y2)) {
				cerr << "core exception : -6, point overlap" << endl;
				throw invalid_argument("point overlap");
			}
			l = new Line(x1, y1, x2, y2, Line::LineType::Line);
			container->insert(*l);
			break;
		case 'R':
			inFile >> x1 >> y1 >> x2 >> y2;
			if (check_point_overlap(x1, y1, x2, y2)) {
				cerr << "core exception : -6, point overlap" << endl;
				throw invalid_argument("point overlap");
			}
			l = new Line(x1, y1, x2, y2, Line::LineType::Ray);
			container->insert(*l);
			break;
		case 'S':
			inFile >> x1 >> y1 >> x2 >> y2;
			if (check_point_overlap(x1, y1, x2, y2)) {
				cerr << "core exception : -6, point overlap" << endl;
				throw invalid_argument("point overlap");
			}
			l = new Line(x1, y1, x2, y2, Line::LineType::Segment);
			container->insert(*l);
			break;
		case 'C':
			inFile >> x1 >> y1 >> x2;
			if (x2 <= 0) throw invalid_argument("r <= 0");
			cir = new Circle(Point(x1, y1), x2);
			container->insert(*cir);
			break;
		default:
			// ERROR
			break;
	}
}
Container* container = new Container();
std::vector<std::string> split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}
int run2() {
	int argc = 5;
	ifstream command("command.pair");
	string str;
	getline(command, str);
	vector<string> ss;
	ss = split(str, ' ');
	const char* arg0 = ss.at(0).c_str();
	const char* arg1 = ss.at(1).c_str();
	const char* arg2 = ss.at(2).c_str();
	const char* arg3 = ss.at(3).c_str();
	const char* arg4 = ss.at(4).c_str();
	const char* args[5]{ arg0, arg1, arg2, arg3, arg4 };
	return 0;// run(argc, (char**)args);
}

void writePoints(unordered_set<Point, myHash>* pointSet) {
	ofstream outPoint("points.txt");
	auto it = pointSet->begin();
	while (it != pointSet->end()) {
		outPoint << (*it).x << " " << (*it).y << endl;
		it++;
	}
	outPoint.close();
}

int main(int argc, char** argv) {
	int n;
	char P;

	ofstream outFile;
	// 异常处理？
	string inFileName, outFileName;
	if (debug) {
		Line l = Line(0, 0, 1, 1, Line::LineType::Line);
		Line l2 = Line(1, 0, 1, 1, Line::LineType::Ray);
		container->insert(l);
		container->insert(l2);
		unordered_set<Point, myHash>* pointSet = finalGetCrossPoints(container->lineVec,
			container->circleVec, debug, testPerform);
		return 0;
	}
	inFileName = argv[2];
	outFileName = argv[4];
	ifstream inFile(inFileName);
	outFile.open(outFileName);
	if (!inFile.is_open() || !outFile.is_open()) {
		cerr << "core exception : -2, file not opened" << endl;
		return -2;
	}

	inFile >> n;
	try {
		while (n--) {
			inFile >> P;
			insertShape(inFile, P, container);
		}
	} catch (exception & e){
		cerr << "core exception : -1, overlap" << endl;
		return -1;
	}
	cout << container->lineVec.size() << endl;
	cout << container->circleVec.size() << endl;
	unordered_set<Point, myHash>* pointSet = finalGetCrossPoints(container->lineVec,
		container->circleVec, debug, testPerform);
	cout << pointSet->size() << endl;
	//system("pause");
	outFile << pointSet->size();
	writePoints(pointSet);
	return 0;
}