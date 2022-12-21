module;
#include "DSL/DslMacros.h"
#include <memory>
#include <sstream>

export module DSL_E.Test_BasicAllocation;

export import DSL.Common;
export import DSL.Containers;
export import DSL.Time;
export import DSL.Text;


export 
namespace dsl::tests
{
	String basicNewTest(UInt64 loopCount = 1000, UInt64 arraySize = 1000)
	{
		class A
		{
		public:
			A(Int64 ia, Int32 ib, Int16 ic) : a(ia), b(ib), c(ic) {};
			Int64 a;
			Int32 b;
			Int16 c;
		};

		Stopwatch sw;
		Vector<Int32> resArrDog;
		Vector<Int32> resArrC;

		Vector<A*> ptrArrDog(arraySize);
		Vector<A*> ptrArrC(arraySize);


		for (UInt64 i = 0; i < loopCount; ++i)
		{
			sw.start();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				A*& temp = ptrArrC[j];
				temp = static_cast<A*>(malloc(sizeof(A)));
				new(temp)A(1, 2, 3);
			}
			sw.stop();
			resArrC.push_back(static_cast<Int32>(sw.getTicksElapsed()));
			sw.reset();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				delete ptrArrC[j];
			}

			sw.start();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				A*& temp = ptrArrDog[j];
				temp = allocMemory<A>();
				constructObject(temp, 1, 2, 3);
			}
			sw.stop();
			resArrDog.push_back(static_cast<Int32>(sw.getTicksElapsed()));
			sw.reset();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				delete (ptrArrDog[j]);
			}
		}

		/*for (UInt64 i = 0; i < loopCount; ++i)
		{

			sw.start();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				A*& temp = ptrArrDog[j];
				temp = allocMemory<A>();
				constructObject(temp, 1, 2, 3);
			}
			sw.stop();
			resArrDog.push_back(static_cast<Int32>(sw.getTicksElapsed()));
			sw.reset();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				delete (ptrArrDog[j]);
			}

			sw.start();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				A*& temp = ptrArrC[j];
				temp = static_cast<A*>(malloc(sizeof(A)));
				new(temp)A(1, 2, 3);
			}
			sw.stop();
			resArrC.push_back(static_cast<Int32>(sw.getTicksElapsed()));
			sw.reset();
			for (UInt64 j = 0; j < arraySize; ++j)
			{
				delete ptrArrC[j];
			}

		}*/


		//Get result
		dsl::Double avarageDog = 0;
		for (auto i : resArrDog)
		{
			avarageDog += i;
		}
		avarageDog = avarageDog / static_cast<dsl::Double>(loopCount);

		dsl::Double avarageC = 0;
		for (auto i : resArrC)
		{
			avarageC += i;
		}
		avarageC = avarageC / static_cast<dsl::Double>(loopCount);

		StringStream resultText1;
		resultText1 << "Standart alloc/contstuct - ";
		resultText1 << "\tAvarage time in ticks : " << avarageC <<
			" (" << dsl::Stopwatch::Tick::toMilliseconds(static_cast<Int64>(avarageC)) << "ms)\n";
		StringStream resultText2;
		resultText2 << "Dog alloc/contstuct - ";
		resultText2 << "\t\tAvarage time in ticks : " << avarageDog <<
			" (" << dsl::Stopwatch::Tick::toMilliseconds(static_cast<Int64>(avarageDog)) << "ms)\n";
		StringStream result;
		result << resultText1.str();
		result << resultText2.str();
		return result.str();
	}
}
