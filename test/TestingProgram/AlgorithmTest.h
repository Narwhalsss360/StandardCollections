#include "Commons.h"
#include "src/CollectionAlgorithm.h"

test_function(reverse)
{
	Array<int, 5> intArray = { 0, 1, 2, 3, 4 };
	auto intArrayOriginal = intArray;
	CollectionAlgorithm::Reverse(intArray);
	for (size_t i = 0, ir = intArray.Length() - 1; i < intArray.Length(); i++, ir--)
		test_expect(intArray[ir], intArrayOriginal[i]);
}

test_function(unique)
{
	Array<int, 10> intArray = { 1, 1, 2, 3, 4, 4, 4, 5, 6, 6 };
	Array<int, 6> uniqueItemsExpected = { 1, 2, 3, 4, 5, 6 };
	auto uniqueItems = CollectionAlgorithm::unique(intArray);
	test_expect(uniqueItems, uniqueItemsExpected);
}

test_function(buuble_sort)
{
	Array<int, 8> intArray = { 54, 562, 2, 3, 54 ,7, 2, 9 };
	Array<int, 8> sortedExpected = { 2, 2, 3, 7, 9, 54, 54, 562 };

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
	int expected2 = 4.5;
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