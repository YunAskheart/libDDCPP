#include "test_utility.h"
#define TEST_OBJECT_AUTO_PROMPT 0
#define DDCPP_DEBUG DD_ON
#include "test_object.hpp"
#include <iostream>
#include "standard/DDUtility.hpp"

inline int func(int x, int y) {
	return x + y;
}

class A {
};
class B : public A {
};

void test_utility() {
	{
		DD::Pair<int, double> idp1(1, 3.3);
		DD::Pair<int, double> idp2(1, 4.1);
		if (idp1 > idp2) {
			throw "'DD::LessThanComparable' test failed.";
		}
	}
	{
		{
			DD::Variant variant_1((Test()));
			if (variant_1.get_type() != typeid(Test)) {
				throw "'DD::Variant' test failed.";
			}
			variant_1 = 2;
			if (variant_1.to<int>() != 2) {
				throw "'DD::Variant' test failed.";
			}
			variant_1 = Test();
			Test tst = variant_1.to<Test>();
			variant_1 = 3.3;
			if (variant_1.to<double>() < 3.0) {
				throw "'DD::Variant' test failed.";
			}
		}
		if (Test::count != 0) {
			throw "'DD::Variant' test failed.";
		}
	}
	{
		DD::Tuple<short, long> tuple_1(3, 2);
		DD::Tuple<short, short> tuple_2(3, 2);
		DD::Tuple<short, long, double> tuple_3(3, 2, 2.0);
		DD::Tuple<short> tuple_4(3);
		if (
			DD::get_value<0>(tuple_1) != 3 ||
			DD::get_value<1>(tuple_1) != 2
		) {
			throw "'DD::Tuple' test failed.";
		}
		if (
			DD::get_value<short>(tuple_1) != 3 ||
			DD::get_value<long>(tuple_1) != 2
		) {
			throw "'DD::Tuple' test failed.";
		}
		/*
		std::cout << (tuple_1 == tuple_3) << std::endl;
		if (
			!(tuple_1 == tuple_2) ||
			tuple_1 == tuple_3 ||
			tuple_1 == tuple_4
		) {
			throw "'DD::Tuple' test failed.";
		}
		*/
	}
	{
		auto testBinded = DD::bind(func, DD::place_holder::_0, 1234);
		if (
			testBinded(1111) != 2345 ||
			testBinded(4321) != 5555
		) {
			throw "'DD::bind' test failed.";
		}
	}
}
