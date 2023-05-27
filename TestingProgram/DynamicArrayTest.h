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

test_function(dynamic_array_join)
{
	DynamicArray<int> mainArray;
	test_expect(mainArray.Capacity(), 0);
	test_expect(mainArray.Length(), 0);
	DynamicArray<int> auxArray;
	test_expect(auxArray.Capacity(), 0);
	test_expect(auxArray.Length(), 0);

	mainArray.Push(0);
	mainArray.Push(1);
	mainArray.Push(4);
	mainArray[2] = 2;
	auxArray.Push(3);
	auxArray.Push(4);

	test_expect(mainArray.Length(), 3);
	test_expect(mainArray[0], 0);
	test_expect(mainArray[1], 1);
	test_expect(mainArray[2], 2);

	test_expect(auxArray.Length(), 2);
	test_expect(auxArray[0], 3);
	test_expect(auxArray[1], 4);

	mainArray.Join(auxArray);
	test_expect(mainArray.Length(), 5);
	test_expect(mainArray[0], 0);
	test_expect(mainArray[1], 1);
	test_expect(mainArray[2], 2);
	test_expect(mainArray[3], 3);
	test_expect(mainArray[4], 4);

	mainArray.Insert(1, auxArray);
	test_expect(mainArray.Length(), 7);
	test_expect(mainArray[0], 0);
	test_expect(mainArray[1], 3);
	test_expect(mainArray[2], 4);
	test_expect(mainArray[3], 1);
	test_expect(mainArray[4], 2);
	test_expect(mainArray[5], 3);
	test_expect(mainArray[6], 4);
}