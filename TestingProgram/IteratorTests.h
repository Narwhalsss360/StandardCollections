#pragma once
#include "Commons.h"

test_function(general_iteration)
{
	int array[] = { 0, 1, 2, 3 };

	test_expect(CStyleLength(array), 4);

	auto begin_iterator = GeneralIterator<int[CStyleLength(array)], int&>(array, 0);
	auto end_iterator = GeneralIterator<int[CStyleLength(array)], int&>(array, CStyleLength(array));

	index_t expectedIndex = 0;
	for (auto i : Iterate(begin_iterator, end_iterator))
	{
		test_expect(i, array[i]);
		expectedIndex++;
	}
}