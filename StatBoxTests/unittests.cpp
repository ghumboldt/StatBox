#include "stdafx.h"
#include "CppUnitTest.h"

#include "StatBox.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StatBoxTests
{		
	TEST_CLASS(UnitTests)
	{
	public:

		TEST_METHOD(TestEmptyConstructor)
		{
			StatBox* stats = new StatBox();

			Assert::AreEqual(DEFAULT_NAME, stats->name().c_str());
			Assert::AreEqual(DEFAULT_UNIT, stats->unit().c_str());
			Assert::AreEqual(size_t(0), stats->size());
		}

		TEST_METHOD(TestConstructorWithName)
		{
			StatBox* stats = new StatBox("Temperature");

			Assert::AreEqual("Temperature", stats->name().c_str());
			Assert::AreEqual(DEFAULT_UNIT, stats->unit().c_str());
			Assert::AreEqual(size_t(0), stats->size());
		}

		TEST_METHOD(TestConstructorWithNameAndUnit)
		{
			StatBox* stats = new StatBox("Temperature", "Kelvin");

			Assert::AreEqual("Temperature", stats->name().c_str());
			Assert::AreEqual("Kelvin", stats->unit().c_str());
			Assert::AreEqual(size_t(0), stats->size());
		}

		TEST_METHOD(TestToString)
		{
			StatBox* stats = new StatBox("Speed", "m/s", 3);

			for (int k = 2; k >= 0; k--)
			{
				stats->set_format(k * 5, k * 2);

				stats->push(10.0 / 3.0);
				Logger::WriteMessage(stats->format().c_str());

				stats->push(3.9);
				Logger::WriteMessage(stats->format().c_str());

				stats->push(65.7);
				Logger::WriteMessage(stats->format().c_str());

				stats->reset();
			}

			Assert::IsTrue(true);
		}

		TEST_METHOD(TestStdDev)
		{
			StatBox* stats = new StatBox("MyValue", "", 3);

			stats->push(1);
			stats->push(3.0);
			stats->push(5);

			Assert::AreEqual(2.0, stats->stddev());
		}

		TEST_METHOD(TestMeanMinMax)
		{
			StatBox* stats = new StatBox("MyValue", "", 3);

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
			StatBox* stats = new StatBox("MyValue", "", 3);

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