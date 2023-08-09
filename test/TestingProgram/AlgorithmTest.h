#include "Commons.h"
#include "src/CollectionAlgorithm.h"

test_function(reverse)
{
	Array<int, 5> intArray = { 0, 1, 2, 3, 4 };
	auto intArrayOriginal = intArray;
	CollectionAlgorithm::Reverse(intArray);
	for (index_t i = 0, ir = intArray.Length() - 1; i < intArray.Length(); i++, ir--)
		test_expect(intArray[ir], intArrayOriginal[i]);
}

test_function(unique)
{
	Array<int, 10> intArray = { 1, 1, 2, 3, 4, 4, 4, 5, 6, 6 };
	Array<int, 6> uniqueItemsExpected = { 1, 2, 3, 4, 5, 6 };
	auto uniqueItems = CollectionAlgorithm::unique(intArray);
	test_expect(uniqueItems, uniqueItemsExpected);
}

test_function(bubble_sort)
{
	Array<int, 8> intArray = { 54, 562, 2, 3, 54 ,7, 2, 9 };
	Array<int, 8> sortedExpected = { 2, 2, 3, 7, 9, 54, 54, 562 };

	test_expect(CollectionAlgorithm::IsSorted(intArray), false);
	test_expect(CollectionAlgorithm::IsSorted(sortedExpected), true);

	CollectionAlgorithm::BubbleSort(intArray);

	for (index_t i = 0; i < intArray.Length(); i++)
		test_expect(intArray[i], sortedExpected[i]);
}

test_function(collection_min)
{
	Array<int, 5> intArray = { 5, 3, 3, 6, 7 };
	int expected = 3;
	test_expect(CollectionAlgorithm::Min(intArray), expected);
}

test_function(collection_max)
{
	Array<int, 5> intArray = { 5, 3, 3, 6, 7 };
	int expected = 7;
	test_expect(CollectionAlgorithm::Max(intArray), expected);
}

test_function(collection_product)
{
	Array<int, 5> intArray = { 5, 3, 3, 6, 7 };
	int expected = 1890;
	test_expect(CollectionAlgorithm::Product(intArray), expected);
}

test_function(collection_sum)
{
	Array<int, 5> intArray = { 5, 3, 3, 6, 7 };
	int expected = 24;
	test_expect(CollectionAlgorithm::Sum(intArray), expected);
}

test_function(collection_average)
{
	Array<double, 5> intArray = { 5, 3, 3, 6, 7 };
	double expected = 4.8;
	test_expect(CollectionAlgorithm::Average(intArray), expected);
}

test_function(collection_median)
{
	Array<int, 5> intArray = { 5, 3, 3, 6, 7 };
	int expected = 3;
	test_expect(CollectionAlgorithm::Median(intArray), expected);

	Array<int, 4> intArray2 = { 5, 3, 6, 7 };
	int expected2 = 4;
	test_expect(CollectionAlgorithm::Median(intArray2), expected2);
}

test_function(collection_factors)
{
	auto factors = CollectionAlgorithm::Factors(12);
	DynamicArray<Array<int, 2>> expectedFactors =
	{
		{ 1, 12 },
		{ 2, 6 },
		{ 3, 4 },
		{ 4, 3 },
		{ 6, 2 },
		{ 12, 1 }
	};

	test_expect(factors, expectedFactors);
}

test_function(collection_prime_factors)
{
	auto primeFactors = CollectionAlgorithm::PrimeFactors(20);
	Array<int, 3> expectedPrimeFactors = { 2, 2, 5 };
	test_expect(primeFactors, expectedPrimeFactors);
}

test_function(collection_lcm)
{
	Array<int, 2> numbers = { 15, 20 };
	int expectedLCM = 60;
	int lcm = CollectionAlgorithm::LCM(numbers);
	test_expect(lcm, expectedLCM);
}

test_function(collection_gcd)
{
	Array<int, 2> numbers = { 15, 20 };
	int expectedGCD = 5;
	int GCD = CollectionAlgorithm::GCD(numbers);
	test_expect(GCD, expectedGCD);
}

test_function(collection_stdev)
{
	Array<double, 3> numbers = { 1, 3, 4 };
	double expectedStdev = 1.52752523165;
	double stdev = CollectionAlgorithm::StandardDeviation(numbers);
	test_expect(int(stdev * 100000000000), int(expectedStdev * 100000000000)); //Round off
}

test_function(insertion_sort)
{
	Array<int, 8> intArray = { 54, 562, 2, 3, 54 ,7, 2, 9 };
	Array<int, 8> sortedExpected = { 2, 2, 3, 7, 9, 54, 54, 562 };

	CollectionAlgorithm::InsertionSort(intArray);

	for (index_t i = 0; i < intArray.Length(); i++)
		test_expect(intArray[i], sortedExpected[i]);
}

test_function(selection_sort)
{
	Array<int, 8> intArray = { 54, 562, 2, 3, 54 ,7, 2, 9 };
	Array<int, 8> sortedExpected = { 2, 2, 3, 7, 9, 54, 54, 562 };

	CollectionAlgorithm::SelectionSort(intArray);

	for (index_t i = 0; i < intArray.Length(); i++)
		test_expect(intArray[i], sortedExpected[i]);
}

test_function(collection_union)
{
	Array<int, 3> a = { 2, 3, 4 }, b = { 4, 5, 6 };
	Array<int, 5> expextedUnion = { 2, 3, 4, 5, 6 };
	auto aob = CollectionAlgorithm::Union(a, b);
	test_expect(aob, expextedUnion);
}

test_function(collection_intersect)
{
	Array<int, 3> a = { 2, 3, 4 }, b = { 4, 5, 6 };
	Array<int, 1> expextedIntersection = { 4 };
	auto aab = CollectionAlgorithm::Intersection(a, b);
	test_expect(aab, expextedIntersection);
}

test_function(collection_weighted_average)
{
	Array<float, 5> nums = { 2, 3, 3 ,4, 5 };
	Array<float, 5> weights = { 0.1, 0.2, 0.3, 0.3, 0.1 };
	float wavg = CollectionAlgorithm::WeightedAverage(nums, weights);
	float expectedWavg = 34.0 / 10.0;
	test_expect(wavg, expectedWavg);
}

test_function(collection_range)
{
	Array<int, 5> nums = { 20, 5, 3, 5, 7 };
	test_expect(CollectionAlgorithm::Range(nums), 17);
}

test_function(collection_correlation_coefficient)
{
	Array<int, 6> x = { 43, 21, 25, 42, 57, 59 }, y = { 99, 65, 79, 75, 87, 81 };
	float cc = CollectionAlgorithm::CorrelationCoefficient(x, y);
	test_expect(isNear(cc, 0.529, 0.001), true);
}

test_function(collection_least_squares_line_slope)
{
	Array<int, 8> x = { 16, 12, 18, 4, 3, 10, 5, 12 }, y = { 87, 88, 89, 68, 78, 80, 75, 83 };
	float lsl = CollectionAlgorithm::LeastSquaresLineSlope(x, y);
	test_expect(isNear(lsl, 1.133, 0.001), true);
}