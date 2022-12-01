#pragma once
#include "DSL/Math/Int/IntMathC.h"
#include "DSL/DslTime.h"
#include "DSL/DslDataStructures.h"
#include "DSL/DslText.h"




namespace dsl::tests::math_c
{
	template<class T>
	String absPerfTest(Int32 loopCount = 1000, Int32 arraySize = 1000)
	{
		Vector<Int64> measureValues(loopCount);
		Stopwatch sw;


		for (Int32 loop = 0; loop < loopCount; ++loop)
		{
			//Init array for calculations
			Vector<T> testV(arraySize);

			for (Int32 i = 0; i < arraySize; ++i)
			{
				testV[i] = -static_cast<T>(i);
			}
			//End Init data for calculations

			sw.start();

			for (Int32 i = 0; i < arraySize; ++i)
			{
				testV[i] = dsl::math_c::integer::abs(testV[i]);
			}

			sw.stop();

			measureValues.push_back(sw.getTicksElapsed());

			sw.reset();
		}

		//Get result
		Double avarage = 0;
		for (auto i : measureValues)
		{
			avarage += i;
		}
		avarage = avarage / static_cast<dsl::Double>(loopCount);

		StringStream resultText;
		resultText << "[math_c]absPerfTest<" << typeid(T).name()
			<< ">\t(loopCount " << loopCount << " | arraySize " << arraySize << ")\n";

		resultText << "Avarage time in ticks : " << avarage <<
			" (" << dsl::Stopwatch::Tick::toMilliseconds(static_cast<Int64>(avarage)) << "ms)\n";

		return resultText.str();
	}
}