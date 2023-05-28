#pragma once
#include "Commons.h"

test_function(general_iteration)
{
	int array[] = { 0, 1, 2, 3 };

	test_expect(CollectionLength(array), 4);

	auto begin_iterator = GeneralIterator<int[CollectionLength(array)], int&>(array, 0);
	auto end_iterator = GeneralIterator<int[CollectionLength(array)], int&>(array, CollectionLength(array));
	index_t expectedIndex = 0;

	for (auto i : Iterate(begin_iterator, end_iterator))
	{
		test_expect(i, array[expectedIndex]);
		expectedIndex++;
	}

	auto begin_enumerator = EnumerationIterator<int[CollectionLength(array)], int&>(array, 0);
	auto end_enumerator = EnumerationIterator<int[CollectionLength(array)], int&>(array, CollectionLength(array));

	auto enumerable = GeneralIteratorWrapper<EnumerationIterator<int[CollectionLength(array)], int&>>(begin_enumerator, end_enumerator);

	expectedIndex = 0;
	for (auto i : Enumerate(begin_enumerator, end_enumerator))
	{
		test_expect(i.defaulted, false);
		test_expect(i.value, array[expectedIndex]);
		test_expect(i.index, expectedIndex);
		expectedIndex++;
	}

	int array2[] = { 1, 2, 3, 4 };
	
	auto begin_zip = ZipIterator<int[CollectionLength(array)], int&>(array, array2, 0);
	auto end_zip = ZipIterator<int[CollectionLength(array)], int&>(array, array2, CollectionLength(array));

	expectedIndex = 0;
	for (auto i : Zip(begin_zip, end_zip))
	{
		test_expect(i.defaulted, false);
		test_expect(i.value1, array[expectedIndex]);
		test_expect(i.value2, array2[expectedIndex]);
		test_expect(i.index, expectedIndex);
		expectedIndex++;
	}
}