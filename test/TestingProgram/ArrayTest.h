#pragma once

#include "Commons.h"

test_function(array_instantiation)
{
	Array<int, 7> bomb_defusal_code = { 7, 3, 5, 5, 6, 0, 8 };
	test_expect(bomb_defusal_code.Length(), 7);
	for (index_t index = 0; index < 7; index++)
		test_expect(bomb_defusal_code[index], bomb_defusal_code_digits[index]);

	Array<int, 3> fill_3 = Array<int, 3>(3);
	for (index_t index = 0; index < 3; index++)
		test_expect(fill_3[index], 3);

	Array_init(double, gen_consts, { 3.1415, 2.7182, 1.414, 1.6180 });

	for (index_t index = 0; index < gen_consts.Length(); index++)
		test_expect(gen_consts[index], Array_init_gen_consts[index]);

	int fibonacci[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	auto array_fibonacci = CStyleToArray(fibonacci);
	for (index_t index = 0; index < array_fibonacci.Length(); index++)
		test_expect(array_fibonacci[index], fibonacci[index]);
}

test_function(array_general_iterator)
{
	Array<int, 7> bomb_defusal_code = { 7, 3, 5, 5, 6, 0, 8 };
	const auto& const_reference__bomb_defusal_code = bomb_defusal_code;

	auto iterable = GeneralIterable<Collection<int>, GeneralIterator<Collection<int>, int&>>(&bomb_defusal_code, 0, 7);

	index_t expectedIndex = 0;
	for (auto& digit : iterable)
	{
		test_expect(digit, bomb_defusal_code_digits[expectedIndex]);
		expectedIndex++;
	}

	expectedIndex = 0;
	for (auto& digit : Iterate(bomb_defusal_code))
	{
		test_expect(digit, bomb_defusal_code_digits[expectedIndex]);
		expectedIndex++;
	}

	expectedIndex = 0;
	for (auto& digit : Iterate(const_reference__bomb_defusal_code))
	{
		test_expect(digit, bomb_defusal_code_digits[expectedIndex]);
		expectedIndex++;
	}

	expectedIndex = 0;
	for (auto digit : Enumerate(bomb_defusal_code))
	{
		test_expect(digit.defaulted, false);
		test_expect(digit.index, expectedIndex);
		test_expect(digit, bomb_defusal_code_digits[expectedIndex]);
		expectedIndex++;
	}

	expectedIndex = 0;
	for (auto digit : Enumerate(const_reference__bomb_defusal_code))
	{
		test_expect(digit.defaulted, false);
		test_expect(digit.index, expectedIndex);
		test_expect(digit, bomb_defusal_code_digits[expectedIndex]);
		expectedIndex++;
	}

	Array<int, 7> bomb_defusal_code_backwards = { 8, 0, 6, 5, 5, 3, 7 };
	const auto& const_ref__bomb_defusal_code_backwards = bomb_defusal_code_backwards;

	expectedIndex = 0;
	for (auto zipping : Zip(bomb_defusal_code, bomb_defusal_code_backwards))
	{
		test_expect(zipping.defaulted, false);
		test_expect(zipping.index, expectedIndex);
		test_expect(zipping.value1, bomb_defusal_code[expectedIndex]);
		test_expect(zipping.value2, bomb_defusal_code_backwards[expectedIndex]);
		expectedIndex++;
	}

	expectedIndex = 0;
	for (auto zipping : Zip(const_reference__bomb_defusal_code, const_ref__bomb_defusal_code_backwards))
	{
		test_expect(zipping.defaulted, false);
		test_expect(zipping.index, expectedIndex);
		test_expect(zipping.value1, bomb_defusal_code[expectedIndex]);
		test_expect(zipping.value2, bomb_defusal_code_backwards[expectedIndex]);
		expectedIndex++;
	}

	expectedIndex = 0;
	for (auto zipping : ZipCopy(const_reference__bomb_defusal_code, const_ref__bomb_defusal_code_backwards))
	{
		test_expect(zipping.defaulted, false);
		test_expect(zipping.index, expectedIndex);
		test_expect(zipping.value1, bomb_defusal_code[expectedIndex]);
		test_expect(zipping.value2, bomb_defusal_code_backwards[expectedIndex]);
		expectedIndex++;
	}
}