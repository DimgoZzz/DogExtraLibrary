#include "DSLTests/Math/Int/IntMathCTests.h"

#include "DSL/Time/Stopwatch.h"
#include <iostream>
#include <vector>

using namespace dsl;
using namespace dsl::math_c::tests;

void dsl::math_c::tests::absPerfTest(Int32 loopCount = 100000, Int32 arraySize = 10000)
{
	std::vector<dsl::Int64> valuesDsl;
	for (int j = 0; j < 100000; ++j)
	{
		//Init data for calculations
		std::vector<dsl::Int8> testV(1000);

		dsl::Stopwatch sw;
		for (dsl::Int64 i = 0; i < static_cast<Int64>(testV.size()); ++i)
		{
			testV[i] = -static_cast<Int8>(i);
		}
		//End Init data for calculations

		sw.start();
		int k = 0;
		for (dsl::Int32 i = 0; i < testV.size(); ++i)
		{
			testV[i] = math_c::integer::abs(testV[i]);
		}
		sw.stop();
		valuesDsl.push_back(sw.getTicksElapsed());

		sw.reset();
	}

	//Get result
	dsl::Double resDsl = 0;
	for (auto i : valuesDsl)
	{
		resDsl += i;
	}
	resDsl = resDsl / static_cast<dsl::Double>(valuesDsl.size());
	std::cout << "dsl math_custom avarage time in ticks: " << resDsl << std::endl;
	std::cout << "(2 10k vector, 100000 loops)" << std::endl;
	int a = 0;
	int b = 0;
	std::cout << "U wanna quit?" << std::endl;
	//cin >> a;
}
