#include "stdafx.h"
#include "CppUnitTest.h"

#include "StatBox.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StatBoxTests
{		
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestStdDev)
		{
			StatBox* stats = new StatBox(3);

			stats->push(1.0);
			stats->push(3.0);
			stats->push(5.0);

			Assert::AreEqual(2.0, stats->stddev());
		}

		TEST_METHOD(TestMeanMinMax)
		{
			StatBox* stats = new StatBox(3);

			stats->push(3.0);
			Assert::AreEqual(3.0, stats->mean());
			Assert::AreEqual(3.0, stats->min());
			Assert::AreEqual(3.0, stats->max());

			stats->push(5.0);
			Assert::AreEqual(4.0, stats->mean());
			Assert::AreEqual(3.0, stats->min());
			Assert::AreEqual(5.0, stats->max());

			stats->push(1.0);
			Assert::AreEqual(3.0, stats->mean());
			Assert::AreEqual(1.0, stats->min());
			Assert::AreEqual(5.0, stats->max());

			stats->push(6.0);
			Assert::AreEqual(4.0, stats->mean()); // (5+1+6)/3
			Assert::AreEqual(1.0, stats->min());
			Assert::AreEqual(6.0, stats->max());

			stats->reset();
			stats->push(3.0);
			Assert::AreEqual(3.0, stats->mean());
			Assert::AreEqual(3.0, stats->min());
			Assert::AreEqual(3.0, stats->max());
		}

		TEST_METHOD(TestLastSizeReset)
		{
			StatBox* stats = new StatBox(3);

			Assert::AreEqual(size_t(0), stats->size());

			stats->push(3.14);
			Assert::AreEqual(size_t(1), stats->size());
			Assert::AreEqual(3.14, stats->last());

			stats->push(4.14);
			Assert::AreEqual(size_t(2), stats->size());
			Assert::AreEqual(4.14, stats->last());

			stats->push(5.14);
			Assert::AreEqual(size_t(3), stats->size());
			Assert::AreEqual(5.14, stats->last());

			stats->push(6.14);
			Assert::AreEqual(size_t(3), stats->size());
			Assert::AreEqual(6.14, stats->last());

			stats->push(7.14);
			Assert::AreEqual(size_t(3), stats->size());
			Assert::AreEqual(7.14, stats->last());

			stats->reset();
			Assert::AreEqual(size_t(0), stats->size());
		}
	};
}