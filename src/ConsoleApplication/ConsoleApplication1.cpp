#include "stdio.h"
#include <iostream>
#include <exception>
#include <fstream>
#include <set>
#include <string>
#include <regex>
#include <sstream>
//.lib文件中仅仅是关于其对应DLL文件中函数的定位信息
#pragma comment(lib,"Dll1.lib")

using namespace std;

extern "C" int __declspec(dllimport) run(int argc, char** argv);
extern "C" int __declspec(dllimport) run2();

set<string> typeSet{ "L", "R", "S", "C" };

void swap(char** a, char** b) {
	auto tmp = a;
	a = b;
	b = tmp;
}
bool checkArgs(int argc, char** argv) {
	if (argc != 5) return false;
	string args[5]{ argv[0], argv[1], argv[2], argv[3], argv[4] };
	if (args[1] == "-i" && args[3] == "-o") {
		return true;
	} else if (args[1] == "-o" && args[3] == "-i") {
		swap(args[1], args[3]);
		swap(args[2], args[4]);
		return true;
	} else {
		return false;
	}
}


void split(const string& s, vector<std::string>& sv, const char delim = ' ') {
	sv.clear();
	std::istringstream iss(s);
	std::string temp;
	while (getline(iss, temp, delim)) {
		sv.emplace_back(std::move(temp));
	}
	return;
}

bool checkNumber(string num) {
	// 不含前导零的整数，范围为 (-100000, 100000)。
	try {
		smatch result;
		regex pattern("([+-]?\\d+)");

		if (!regex_match(num, result, pattern)) {
			return false;
		}
		int n = stoi(num);
		if (n >= 100000 || n <= -100000) return false;
		if (num.at(0) == '0' && n != 0 || 
			num.length() > 2 && (num.at(0) == '-' || num.at(0) == '+')
				&& num.at(1) == '0') return false;
	} catch (std::invalid_argument& e) {
		// if no conversion could be performed
		return false;
	}
	return true;
}

int checkFirstLine(string s) {
	smatch result;
	regex pattern("(\\d+)");

	if (regex_match(s, result, pattern)) {
		if (s.at(0) == '0') return -1;
		return stoi(s);
	}
	return -1;
}

template<typename T>
void myassert(T b1, T b2) {
	if (b1 != b2) throw exception("assert failed");
}

bool checkOneLine(string s) {
	vector<string> ss;
	split(s, ss);
	if (ss.size() == 0) {
		cerr << "console exception:-4, checkOneLine" << endl;
		return false;
	}
	string types = ss.at(0);
	if (typeSet.find(types) == typeSet.end()) return false;
	try {
		if (types == "L" || types == "R" || types == "S") {
			myassert(5, (int)ss.size());
		} else {
			myassert(4, (int)ss.size());
		}
		for (int i = 1; i < ss.size(); i ++) {
			myassert(checkNumber(ss.at(i)), true);
		}
	} catch (exception e) {
		cerr << "console exception:-4, checkOneLine" << endl;
		return false;
	}
	return true;
}

bool checkFiles(char* inFileName, char* outFileName) {
	ifstream inFile(inFileName);
	ofstream outFile(outFileName);
	if (!inFile.is_open() || !outFile.is_open()) {
		cerr << "checkfile exception : -3, file not opened" << endl;
		return false;
	}
	// 考虑的输入为以大小写字母，数字，空格，-，\n 组成的文本。
	string str;
	getline(inFile, str);
	if (str.empty()) return false;
	int n;
	try {
		n = checkFirstLine(str);
	}
	catch (std::invalid_argument&) {
		cerr << "checkfile exception:-4, checkFirstLine fail" << endl;
		return false;
	}
	if (n == -1) return false;
	for (int i = 0; i < n; i++) {
		if (!inFile.eof()) getline(inFile, str);
		else {
			cerr << "checkfile exception:-5, Linesize no match" << endl;
			return false;
		}
		if (!checkOneLine(str)) {
			cerr << "checkfile exception:-4, checkOneLine" << endl;
			return false;
		}
	}
	if (!inFile.eof()) {
		getline(inFile, str);
		smatch result;
		if (str.length() > 0 && !regex_match(str, result, regex("(\\s+)"))) {
			cerr << "checkfile exception:-5, Line size no match" << endl;
			return false;
		}
		
	}
	inFile.close();
	outFile.close();
	return true;
}

int main(int argc, char** argv) {
	//int result2 = run2();
	//return result2;
	if (!checkArgs(argc, argv)) {
		cerr << "console exception : -2, error args" << endl;
		return -2;
	}

	if (!checkFiles(argv[2], argv[4])) {
		cerr << "console exception : -4, file check fail" << endl;
		return -4;
	}
	
	int result = run(argc, argv);
	switch (result) {
		case -1:
			cerr << "console exception : -1, overlap" << endl;
			return -1;
			break;
		default:
			break;

	}
	return 0;
}
