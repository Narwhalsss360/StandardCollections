#pragma once

#include "Commons.h"

test_function(dynamic_array)
{
	DynamicArray<int> array;
	test_expect(array.Capacity(), 0);
	test_expect(array.Length(), 0);

	array.Push(0);
	array.Push(1);
	array.Push(2);
	array.Push(3);
	array.Push(4);
	test_expect(array.Length(), 5);
	test_expect(array[0], 0);
	test_expect(array[1], 1);
	test_expect(array[2], 2);
	test_expect(array[3], 3);
	test_expect(array[4], 4);

	int popped = array.Pop();
	test_expect(popped, 4);
	test_expect(array.Length(), 4);
	test_expect(array[0], 0);
	test_expect(array[1], 1);
	test_expect(array[2], 2);
	test_expect(array[3], 3);

	array.Insert(1, popped);
	test_expect(array.Length(), 5);
	test_expect(array[0], 0);
	test_expect(array[1], 4);
	test_expect(array[2], 1);
	test_expect(array[3], 2);
	test_expect(array[4], 3);

	array.Unshift(array.Pop());
	test_expect(array.Length(), 5);
	test_expect(array[0], 3);
	test_expect(array[1], 0);
	test_expect(array[2], 4);
	test_expect(array[3], 1);
	test_expect(array[4], 2);

	array.Remove(2, 1);
	test_expect(array.Length(), 4);
	test_expect(array[0], 3);
	test_expect(array[1], 0);
	test_expect(array[2], 1);
	test_expect(array[3], 2);

	array.Remove(1);
	test_expect(array.Length(), 2);
	test_expect(array[0], 3);
	test_expect(array[1], 0);
}