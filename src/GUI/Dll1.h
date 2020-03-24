// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DLL1_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DLL1_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

#pragma once

#include "line.h"
#include "shape.h"
#include "circle.h"
#include <unordered_set>
#include "shape.h"
#include "line.h"
using namespace std;

struct myHash {
	size_t operator()(const Point& obj) const {
		return hash<double>()(obj.x + obj.y);
	}
};

bool double_equal(double a, double b) {
	return a == b;
}
bool operator ==(const Point& obj, const Point& obj2) {
	return double_equal(obj.x, obj2.x) && double_equal(obj.y, obj2.y);
}
extern "C" DLL1_API unordered_set<Point, myHash> * finalGetCrossPoints(vector<Line*> lineVec, vector<Circle*> circleVec,
	bool debug, bool testPerform);
extern "C" DLL1_API int run(int argc, char** argv);
extern "C" DLL1_API int run2();