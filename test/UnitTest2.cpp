#include "pch.h"
#include "CppUnitTest.h"
#include "../src/container.h"
#include "../src/line.h"
#include "../src/circle.h"
#include "../src/shape.h"
#include "../src/main.cpp"
#include "../src/ConsoleApplication1/ConsoleApplication1.cpp";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
		
			Container c;
			Line l1(0, 0, 1, 1, Line::LineType::Line);
			Line l2(0, 0, 1, 1, Line::LineType::Ray);
			Line l3(0, 0, 3, 3, Line::LineType::Ray);
			Line l4(0, 0, -3, -3, Line::LineType::Ray);
			Line l5(1, 1, 3, 3, Line::LineType::Ray);
			Line l6(1, 1, -1, -1, Line::LineType::Ray);
			Assert::AreEqual(true, c.equal(l2, l3));
			Assert::AreEqual(false, c.equal(l3, l4));
			Assert::AreEqual(false, c.equal(l4, l5));
			Assert::AreEqual(true, c.equal(l3, l6));
			Shape sh;
			Shape sh2;
			auto p222 = sh.getCross(&sh2);
			Point np;
			Assert::AreEqual(true, p222.equal(np));
			
		}
		
		TEST_METHOD(TestMethod2) {
			Container c;
			Line l1(0, 0, 0, 1, Line::LineType::Ray);
			Line l2(0, -1, 0, 1, Line::LineType::Ray);
			Line l3(0, -1, 0, -2, Line::LineType::Ray);
			Line l4(0, 0, 0, -1, Line::LineType::Ray);
			Assert::AreEqual(true, c.equal(l1, l2));
			Assert::AreEqual(false, c.equal(l2, l3));
			Assert::AreEqual(true, c.equal(l3, l4));
			Assert::AreEqual(false, c.equal(l1, l4));
		}

		TEST_METHOD(TestMethod3) {
			Container c;
			Line s1(0, 0, 1, 1, Line::LineType::Segment);
			Line s2(0, 0, 2, 2, Line::LineType::Segment);
			Line s3(-1, -1, 0, 0, Line::LineType::Segment);
			Line s4(0, 0, 0, 1, Line::LineType::Segment);
			Line s5(0, 0, 0, 2, Line::LineType::Segment);
			Line s6(0, 3, 0, 4, Line::LineType::Segment);
			Assert::AreEqual(true, c.equal(s1, s2));
			Assert::AreEqual(false, c.equal(s1, s3));
			Assert::AreEqual(true, c.equal(s4, s5));
			Assert::AreEqual(true, c.equal(s5, s6));
		}
		TEST_METHOD(RayAndSegment) {
			Container c;
			Line s1(0, 0, 1, 1, Line::LineType::Segment);
			Line s3(-1, -1, 0, 0, Line::LineType::Segment);
			Line s4(0, 0, 0, 1, Line::LineType::Segment);
			Line s6(0, 3, 0, 4, Line::LineType::Segment);
			Line l1(0, 0, 0, 1, Line::LineType::Ray);
			Line l7(0, 0, 0, -1, Line::LineType::Ray);
			Line l2(0, 0, 1, 1, Line::LineType::Ray);
			Line l3(0, 0, 3, 3, Line::LineType::Ray);
			Line l4(0, 0, -3, -3, Line::LineType::Ray);
			Assert::AreEqual(true, c.equal(s1, l2));
			Assert::AreEqual(false, c.equal(s1, s4));
			Assert::AreEqual(true, c.equal(s3, l4));
			Assert::AreEqual(true, c.equal(s4, l1));
			Assert::AreEqual(false, c.equal(s4, l7));
			Assert::AreEqual(false, c.equal(s6, l7));
			Assert::AreEqual(true, c.equal(s6, l1));
		}
		TEST_METHOD(EdgeNumber) {
			Line l1(-99999, -99999, 99999, 99999, Line::LineType::Ray);
			Line l2(-99998, -99998, 99998, 99998, Line::LineType::Segment);
			Line l3(-99999, -99999, 99997, 99997, Line::LineType::Segment);
			Line l4(99998, 99998, 99999, 99999, Line::LineType::Segment);
			Container c;
			Assert::AreEqual(true, c.equal(l1, l2));
			Assert::AreEqual(true, c.equal(l2, l3));
			Assert::AreEqual(false, c.equal(l3, l4));
		}
	};
	TEST_CLASS(UnitTeset3) {
	public:

	TEST_METHOD(TestMethod1) {
		Line l1(0, 0, 1, 1, Line::LineType::Line);
		Line l2(0, 0, -1, 1, Line::LineType::Ray);
		Line l3(1, 0, 0, 1, Line::LineType::Ray);
		Line l4(-1, 3, -3, 2, Line::LineType::Segment);
		Line l5(1, 4, 2, 3, Line::LineType::Segment);
		Line l6(3, 0, 2, -1, Line::LineType::Segment);
		Line l7(0, -2, 0, 3, Line::LineType::Ray);
		Point p;
		p = l1.getCross(&l2);
		Assert::AreEqual(true, p.valid);
		p = l1.getCross(&l3);
		Assert::AreEqual(true, p.valid);
		p = l1.getCross(&l5);
		Assert::AreEqual(false, p.valid);
		p = l1.getCross(&l4);
		Assert::AreEqual(false, p.valid);
		p = l1.getCross(&l7);
		Assert::AreEqual(true, p.valid);
		p = l2.getCross(&l4);
		Assert::AreEqual(true, p.valid);
		p = l3.getCross(&l4);
		Assert::AreEqual(true, p.valid);
		p = l2.getCross(&l7);
		Assert::AreEqual(true, p.valid);
		p = l2.getCross(&l6);
		Assert::AreEqual(false, p.valid);
		p = l7.getCross(&l5);
		Assert::AreEqual(false, p.valid);
		p = l5.getCross(&l6);
		Assert::AreEqual(false, p.valid);
	}

	TEST_METHOD(CircleAndLine) {
		Circle c(Point(0,0),4);
		Circle c2(Point(0, 0), 4);
		Line l(0, 0, 1, 1, Line::LineType::Line);
		Container con;
		Assert::AreEqual(true, con.equal(c, c2));
		Assert::AreEqual(false, con.equal(l, c));
		Line BC(2, 3, 0, 1, Line::LineType::Segment);
		Circle A(Point(0, 0), 2);
		Line BD(2, 3, 2, 0, Line::LineType::Line);
		Line EF(-3, -2, 0, 1, Line::LineType::Ray);
		Line GH(-3, 3, -2, 2, Line::LineType::Segment);
		Line IJ(-4, 3, -3, 4, Line::LineType::Segment);
		Line KL(0, 3, 0, 4, Line::LineType::Ray);
		Circle M(Point(-5, 0), 4);
		Point p;
		pointPair pair;
		pair = getCrossPoints(&A, &BD);
		Assert::AreEqual(1, pair.first.valid & pair.second.valid);
		Assert::AreEqual(true, pair.first.equal(pair.second));
		pair = getCrossPoints(&A, &BC);
		Assert::AreEqual(1, pair.first.valid ^ pair.second.valid);
		pair = getCrossPoints(&A, &EF);
		Assert::AreEqual(1, pair.first.valid & pair.second.valid);
		pair = getCrossPoints(&A, &GH);
		Assert::AreNotEqual(1, pair.first.valid | pair.second.valid);
		pair = getCrossPoints(&M, &EF);
		Assert::AreNotSame(pair.first.valid, pair.second.valid);
		pair = getCrossPoints(&M, &IJ);
		Assert::AreNotSame(pair.first.valid, pair.second.valid);
		pair = getCrossPoints(&M, &GH);
		Assert::AreNotEqual(1, pair.first.valid | pair.second.valid);
		con.insert(BD);
		con.insert(A);
		con.insert(EF);
		con.insert(GH);
		con.insert(IJ);
		con.insert(KL);
		con.insert(M);
		auto set = finalGetCrossPoints(con.lineVec, con.circleVec, true, false);
		Assert::AreEqual(8, (int)set->size());
	}
	};

	TEST_CLASS(UnitTeset4) {
	public:
		TEST_METHOD(runtest) {
			char * s[5];
			s[1] = "-i";
			s[2] = "in.txt";
			s[3] = "-o";
			s[4] = "out.txt";
			int rt=	run(5, s);
			Assert::AreEqual(-2, rt);
			s[2] = "in2.txt";
			rt = run(5, s);
			Assert::AreEqual(-1, rt);
			s[2] = "in3.txt";
			rt = run(5, s);
			Assert::AreEqual(-1, rt);
		}
		
		TEST_METHOD(consoletest) {
			
			char* s[5];
			s[0] = "duadhk";
			s[1] = "-2";
			s[2] = "in.txt";
			s[3] = "-o";
			s[4] = "out.txt";
			int rt = main(5, s);
			Assert::AreEqual(-2, rt);
			s[2] = "in2.txt";
			rt = main(4, s);
			Assert::AreEqual(-2, rt);
			s[1] = "-i";
			s[2] = "in.txt";
			rt = main(5, s);
			Assert::AreEqual(-4, rt);
			s[2] = "in4.txt";
			rt = main(5, s);
			Assert::AreEqual(-4, rt);
			s[2] = "in5.txt";
			rt = main(5, s);
			Assert::AreEqual(-4, rt);
			s[2] = "in6.txt";
			rt = main(5, s);
			Assert::AreEqual(-4, rt);
			s[2] = "in7.txt";
			rt = main(5, s);
			Assert::AreEqual(-4, rt);
			s[2] = "in8.txt";
			rt = main(5, s);
			Assert::AreEqual(-4, rt);
			s[2] = "D:\\qnmdC\\SE\\test\\in2.txt";
			rt = main(5, s);
			Assert::AreEqual(-1, rt);
			s[2] = "in9.txt";
			rt = main(5, s);
			Assert::AreEqual(-1, rt);
			s[2] = "in10.txt";
			rt = main(5, s);
			Assert::AreEqual(-4, rt);
			rt =  run2();
			Assert::AreEqual(-1, rt);
			s[2] = "in11.txt";
			rt = main(5, s);
			Assert::AreEqual(-1, rt);
			s[2] = "in12.txt";
			rt = main(5, s);
			Assert::AreEqual(-1, rt);
			s[2] = "in13.txt";
			rt = main(5, s);
			Assert::AreEqual(-1, rt);
			s[1] = "-o";
			s[3] = "-i";
			rt = main(5, s);
			Assert::AreEqual(-1, rt);
			
			
		}
		
		
	};
	
}
