#include "stdafx.h"
#include "CppUnitTest.h"

#include "StatBox.h"
#include <math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StatBoxTests
{		
	TEST_CLASS(UnitTests)
	{
	public:

		TEST_METHOD(TestEmptyConstructor)
		{
			auto stats = StatBox();

			Assert::AreEqual(DEFAULT_NAME, stats.get_name().c_str());
			Assert::AreEqual(DEFAULT_UNIT, stats.get_unit().c_str());
			Assert::AreEqual(size_t(0), stats.get_valid_values());
		}

		TEST_METHOD(TestConstructorWithName)
		{
			auto stats = StatBox("Temperature");

			Assert::AreEqual("Temperature", stats.get_name().c_str());
			Assert::AreEqual(DEFAULT_UNIT, stats.get_unit().c_str());
			Assert::AreEqual(size_t(0), stats.get_valid_values());
		}

		TEST_METHOD(TestConstructorWithNameAndUnit)
		{
			StatBox stats = StatBox("Temperature", "Kelvin");
			stats.push(3.14);

			Assert::AreEqual("Temperature", stats.get_name().c_str());
			Assert::AreEqual("Kelvin", stats.get_unit().c_str());
			Assert::AreEqual(size_t(1), stats.get_valid_values());
		}

		TEST_METHOD(TestConstructorWithCapacity)
		{
			StatBox stats = StatBox("Temperature", "Kelvin", 15);

			for (int k = 0; k < 20; k++) // push 20 but capacity is 15
			{
				stats.push(42.0);
			}

			Assert::AreEqual(size_t(15), stats.get_valid_values());

			stats.reset();
			Assert::AreEqual(size_t(0), stats.get_valid_values());
		}

		TEST_METHOD(TestConstructorWithDrop)
		{
			StatBox stats = StatBox("Temperature", "Kelvin", 15, 5);

			for (int k = 0; k < 5; k++) // push 5 which should get dropped
			{
				stats.push(42.0);
			}

			Assert::AreEqual(size_t(0), stats.get_valid_values());

			stats.push(17.0); // first value not dropped?

			Assert::AreEqual(size_t(1), stats.get_valid_values());
			Assert::AreEqual(17.0, stats.get_min());
			Assert::AreEqual(17.0, stats.get_max());
			Assert::AreEqual(17.0, stats.get_mean());
			Assert::AreEqual(0.0, stats.get_std());

			stats.push(19.0); // second value not dropped?

			Assert::AreEqual(size_t(2), stats.get_valid_values());
			Assert::AreEqual(17.0, stats.get_min());
			Assert::AreEqual(19.0, stats.get_max());
			Assert::AreEqual(18.0, stats.get_mean());
			Assert::AreEqual(sqrt(2.0), stats.get_std());

			stats.reset(); // ensure same behaviour after reset

			for (int k = 0; k < 5; k++) // push 5 which should get dropped
			{
				stats.push(42.0);
			}

			Assert::AreEqual(size_t(0), stats.get_valid_values());

			stats.push(17.0); // first value not dropped?

			Assert::AreEqual(size_t(1), stats.get_valid_values());
			Assert::AreEqual(17.0, stats.get_min());
			Assert::AreEqual(17.0, stats.get_max());
			Assert::AreEqual(17.0, stats.get_mean());
			Assert::AreEqual(0.0, stats.get_std());

			stats.push(19.0); // second value not dropped?

			Assert::AreEqual(size_t(2), stats.get_valid_values());
			Assert::AreEqual(17.0, stats.get_min());
			Assert::AreEqual(19.0, stats.get_max());
			Assert::AreEqual(18.0, stats.get_mean());
			Assert::AreEqual(sqrt(2.0), stats.get_std());
		}

		TEST_METHOD(TestToString)
		{
			auto stats = StatBox("Speed", "m/s", 3);

			for (int k = 2; k >= 0; k--)
			{
				stats.set_format(k * 5, k * 2);

				stats.push(10.0 / 3.0);
				Logger::WriteMessage(stats.get_string().c_str());

				stats.push(3.9);
				Logger::WriteMessage(stats.get_string().c_str());

				stats.push(65.7);
				Logger::WriteMessage(stats.get_string().c_str());

				stats.reset();
			}

			Assert::IsTrue(true);
		}

		TEST_METHOD(TestStdDev)
		{
			auto stats = StatBox("MyValue", "", 3);

			stats.push(1);
			stats.push(3.0);
			stats.push(5);

			Assert::AreEqual(2.0, stats.get_std());
		}

		TEST_METHOD(TestMeanMinMax)
		{
			auto stats = StatBox("MyValue", "", 3);

			stats.push(3.0);
			Assert::AreEqual(3.0, stats.get_mean());
			Assert::AreEqual(3.0, stats.get_min());
			Assert::AreEqual(3.0, stats.get_max());

			stats.push(5.0);
			Assert::AreEqual(4.0, stats.get_mean());
			Assert::AreEqual(3.0, stats.get_min());
			Assert::AreEqual(5.0, stats.get_max());

			stats.push(1.0);
			Assert::AreEqual(3.0, stats.get_mean());
			Assert::AreEqual(1.0, stats.get_min());
			Assert::AreEqual(5.0, stats.get_max());

			stats.push(6.0);
			Assert::AreEqual(4.0, stats.get_mean()); // (5+1+6)/3
			Assert::AreEqual(1.0, stats.get_min());
			Assert::AreEqual(6.0, stats.get_max());

			stats.reset();
			stats.push(3.0);
			Assert::AreEqual(3.0, stats.get_mean());
			Assert::AreEqual(3.0, stats.get_min());
			Assert::AreEqual(3.0, stats.get_max());
		}

		TEST_METHOD(TestLastSizeReset)
		{
			auto stats = StatBox("MyValue", "", 3);

			Assert::AreEqual(size_t(0), stats.get_valid_values());

			stats.push(3.14);
			Assert::AreEqual(size_t(1), stats.get_valid_values());
			Assert::AreEqual(3.14, stats.get_last_value());

			stats.push(4.14);
			Assert::AreEqual(size_t(2), stats.get_valid_values());
			Assert::AreEqual(4.14, stats.get_last_value());

			stats.push(5.14);
			Assert::AreEqual(size_t(3), stats.get_valid_values());
			Assert::AreEqual(5.14, stats.get_last_value());

			stats.push(6.14);
			Assert::AreEqual(size_t(3), stats.get_valid_values());
			Assert::AreEqual(6.14, stats.get_last_value());

			stats.push(7.14);
			Assert::AreEqual(size_t(3), stats.get_valid_values());
			Assert::AreEqual(7.14, stats.get_last_value());

			stats.reset();
			Assert::AreEqual(size_t(0), stats.get_valid_values());
		}
	};
}