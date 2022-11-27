#pragma once
#include "DSL/Math/Int/IntMathC.h"
#include "DSL/Time/Stopwatch.h"

#include <vector>
#include <string>
#include <typeinfo>
#include <sstream>


namespace dsl::math_c::tests
{
	template<class T>
	std::string absPerfTest(Int32 loopCount = 1000, Int32 arraySize = 1000)
	{
		std::vector<dsl::Int64> measureValues(loopCount);
		dsl::Stopwatch sw;


		for (int loop = 0; loop < loopCount; ++loop)
		{
			//Init array for calculations
			std::vector<T> testV(arraySize);

			for (dsl::Int32 i = 0; i < arraySize; ++i)
			{
				testV[i] = -static_cast<T>(i);
			}
			//End Init data for calculations

			sw.start();

			for (dsl::Int32 i = 0; i < arraySize; ++i)
			{
				testV[i] = dsl::math_c::integer::abs(testV[i]);
			}

			sw.stop();

			measureValues.push_back(sw.getTicksElapsed());

			sw.reset();
		}

		//Get result
		dsl::Double avarage = 0;
		for (auto i : measureValues)
		{
			avarage += i;
		}
		avarage = avarage / static_cast<dsl::Double>(loopCount);

		std::stringstream resultText;
		resultText << "[math_c]absPerfTest<" << typeid(T).name()
			<< ">\t(loopCount " << loopCount << " | arraySize " << arraySize << ")" << std::endl;

		resultText << "Avarage time in ticks : " << avarage <<
			" (" << dsl::Stopwatch::Tick::toMilliseconds(static_cast<Int64>(avarage)) << "ms)" << std::endl;
		resultText << std::endl;

		return resultText.str();
	}
}