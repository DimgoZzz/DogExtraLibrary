#pragma once
#include "DSL/Math/Int/IntMathCustom.h"
#include "DSL/DslTime.h"
#include "DSL/DslDataStructures.h"
#include "DSL/DslText.h"



namespace dsl::tests::math_custom
{
	//Benchmark for Int8/16/32/64/Float/Double of math_custom
	template<class T>
	String absTest(Int32 loopCount = 1000, Int32 arraySize = 1000)
	{
		Vector<Int64> measureValues(loopCount);
		Stopwatch sw;

		Vector<T> testV(arraySize);

		for (Int32 loop = 0; loop < loopCount; ++loop)
		{
			//Init array for calculations
			for (Int32 i = 0; i < arraySize; ++i)
			{
				testV[i] = -(static_cast<T>(i));
			}

			sw.start();
			for (Int32 i = 0; i < arraySize; ++i)
			{
				testV[i] = dsl::math_custom::integer::abs(testV[i]);
			}
			sw.stop();

			measureValues.push_back(sw.getTicksElapsed());

			sw.reset();
		}

		//Get result
		Double avarage = 0;
		//Sum all results
		for (auto i : measureValues)
		{
			avarage += i;
		}
		//Get avarage
		avarage = avarage / static_cast<dsl::Double>(loopCount);

		StringStream resultText;
		resultText << "math_custom::absTest<" << typeid(T).name() 
		<< ">\t(loopCount " << loopCount << " | arraySize " << arraySize <<")\n";

		resultText << "Avarage time in ticks : " << avarage <<
			" (" << dsl::Stopwatch::Tick::toMilliseconds(static_cast<Int64>(avarage))<< "ms)\n";

		return resultText.str();
	}
}