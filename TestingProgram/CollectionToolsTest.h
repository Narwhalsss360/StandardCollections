#pragma once
#include "Commons.h"

bool is4(const int& number)
{
	return number == 4;
}

test_function(finding_elements)
{
	Array_init(int, array, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 8 });

	auto finding1 = array.Find(4);
	test_expect(finding1.valid, true);
	test_expect(finding1.index, 4);
	test_expect(finding1.value, 4);

	auto finding2 = array.Find(is4);
	test_expect(finding2.valid, true);
	test_expect(finding2.index, 4);
	test_expect(finding2.value, 4);

	auto finding3 = array.Find(8);
	test_expect(finding3.valid, true);
	test_expect(finding3.index, 8);
	test_expect(finding3.value, 8);

	auto finding4 = array.FindLast(8);
	test_expect(finding4.valid, true);
	test_expect(finding4.index, 9);
	test_expect(finding4.value, 8);
}

void TestIfValueIsIndex(const index_t index, const int& value)
{
	test_expect(index, value);
}

void SetToZero(const index_t, int& number)
{
	number = 0;
}

void TestIfZero(const index_t, const int& number)
{
	test_expect(number, 0);
}

test_function(for_each)
{
	Array<int, 5> inOrderNumbers = { 0, 1, 2, 3, 4, 5 };
	inOrderNumbers.ForEach(TestIfValueIsIndex);
	Array<int, 10> justNumbers;
	inOrderNumbers.ForEach(SetToZero);
}

test_function(comparators)
{
	Array<int, 5> array1 = { 0 , 1, 2, 3, 4, };
	Array<int, 5> array2 = { 0 , 1, 2, 3, 4, };
	Array<int, 3> array3 = { 0 , 1, 2 };

	test_expect(array1 == array1, true);

	test_expect(array1 == array2, true);
	test_expect(array1 < array2, false);
	test_expect(array1 <= array2, true);
	test_expect(array1 > array2, false);
	test_expect(array1 >= array2, true);

	test_expect(array1 == array3, false);
	test_expect(array1 < array3, false);
	test_expect(array1 <= array3, false);
	test_expect(array1 > array3, true);
	test_expect(array1 >= array3, true);
}