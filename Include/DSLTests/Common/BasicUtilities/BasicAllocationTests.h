#pragma once
#include "DSL/DslMinimal.h"
#include "DSL/DslText.h"
#include "DSL/DslTime.h"
#include "DSL/DslDataStructures.h"

namespace dsl::tests
{
	String AllocConstructPerfTest(UInt64 loopCount = 1000, UInt64 arraySize = 1000)
	{
		class A
		{
		public:
			Int64 a;
			Int32 b;
			Int16 c;
		};

		Stopwatch sw;
		Vector<Int32> resArr1;
		Vector<Int32> resArr2;

		Vector<A*> ptrArr1(arraySize);
		Vector<A*> ptrArr2(arraySize);


		for (UInt64 i = 0; i < loopCount; ++i)
		{
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				ptrArr1[j] = new A;
			}
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				delete (ptrArr1[j]);
			}
		}
		for (UInt64 i = 0; i < loopCount; ++i)
		{
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				ptrArr2[j] = static_cast<A*>(dMalloc(sizeof(A)));
			}
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				delete ptrArr2[j];
			}
		}

		for (UInt64 i = 0; i < loopCount; ++i)
		{
			sw.start();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				ptrArr2[j] = static_cast<A*>(dMalloc(sizeof(A)));
				new(ptrArr2[j])A();
			}
			sw.stop();
			resArr2.push_back(static_cast<Int32>(sw.getTicksElapsed()));
			sw.reset();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				delete ptrArr2[j];
			}
		}

		for (UInt64 i = 0; i < loopCount; ++i)
		{
			sw.start();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				ptrArr1[j] = new A;
				dConstruct(ptrArr1[j]);
			}
			sw.stop();
			resArr1.push_back(static_cast<Int32>(sw.getTicksElapsed()));
			sw.reset();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				delete (ptrArr1[j]);
			}
		}



		//Get result
		dsl::Double avarage1 = 0;
		for (auto i : resArr1)
		{
			avarage1 += i;
		}
		avarage1 = avarage1 / static_cast<dsl::Double>(loopCount);

		StringStream resultText1;
		resultText1 << "Standart new - ";
		resultText1 << "Avarage time in ticks : " << avarage1 <<
			" (" << dsl::Stopwatch::Tick::toMilliseconds(static_cast<Int64>(avarage1)) << "ms)\n";

		dsl::Double avarage2 = 0;
		for (auto i : resArr2)
		{
			avarage2 += i;
		}
		avarage2 = avarage2 / static_cast<dsl::Double>(loopCount);

		StringStream resultText2;
		resultText2 << "Custom new - ";
		resultText2 << "Avarage time in ticks : " << avarage2 <<
			" (" << dsl::Stopwatch::Tick::toMilliseconds(static_cast<Int64>(avarage2)) << "ms)\n";
		StringStream result;
		result << resultText1.str();
		result << resultText2.str();
		return result.str();
	}
}
