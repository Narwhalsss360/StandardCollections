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

test_function(slice)
{
	Array<int, 10> array;

 	for (index_t i = 0; i < array.Length(); i++)
		array[i] = i;

	test_standard_output_write("\n");

	auto sliced1 = array.Slice(0, 7);

	test_standard_output_write("\n");

	for (index_t i = 0; i < sliced1.Length(); i++)
		test_expect(sliced1[i], i);

	auto sliced2 = array.Slice(4);

	for (auto enumeration : Enumerate(sliced2))
		test_expect(enumeration.value, enumeration.index + 4);
}

ContainerC CastAToC(ContainerA& A)
{
	ContainerC out;
	out.number = A.number;
	return out;
}

ContainerB CastAToB(ContainerA& A)
{
	ContainerB out;
	out.precision = (float)A.number;
	return out;
}

test_function(collection_casts)
{
	Array<ContainerA, 3> aTypeArray;
	aTypeArray[0] = { 0 };
	aTypeArray[1] = { -1 };
	aTypeArray[2] = { 2 };

	test_expect(aTypeArray[0].number, 0);
	test_expect(aTypeArray[1].number, -1);
	test_expect(aTypeArray[2].number, 2);

	Array<ContainerC, 3> cTypeArrayCasted;

	CastCollection(aTypeArray, cTypeArrayCasted, CastAToC);

	test_expect(cTypeArrayCasted[0].number, 0);
	test_expect(cTypeArrayCasted[1].number, -1);
	test_expect(cTypeArrayCasted[2].number, 2);
	test_expect(cTypeArrayCasted[0].precision, 0.0f);
	test_expect(cTypeArrayCasted[1].precision, 0.0f);
	test_expect(cTypeArrayCasted[2].precision, 0.0f);
	test_expect(cTypeArrayCasted[0].string, "default");
	test_expect(cTypeArrayCasted[1].string, "default");
	test_expect(cTypeArrayCasted[2].string, "default");

	Array<ContainerC, 3> cTypeArray;

	cTypeArray[0] = ContainerC(-1, 1.1, "i0");
	cTypeArray[1] = ContainerC(-2, 2, "i1");
	cTypeArray[2] = ContainerC(-3, 3, "i2");

	Array<ContainerA, 3> aTypeCasted;

	CastCollection(cTypeArray, aTypeCasted);

	test_expect(aTypeCasted[0].number, -1);
	test_expect(aTypeCasted[1].number, -2);
	test_expect(aTypeCasted[2].number, -3);

	Array<ContainerB, 3> bTypeCasted;

	CastCollection(aTypeArray, bTypeCasted, CastAToB);

	test_expect(bTypeCasted[0].precision, 0);
	test_expect(bTypeCasted[1].precision, -1);
	test_expect(bTypeCasted[2].precision, 2);
}