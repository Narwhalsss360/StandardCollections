#pragma once

#include "Commons.h"
#include "StandardCollections.h"

test_function(Array_instantiation_test)
{
	Array<int, 7> bomb_defusal_code = { 7, 3, 5, 5, 6, 0, 8 };
	test_expect(bomb_defusal_code.length(), 7);
	for (size_t index = 0; index < 7; index++)
		test_expect(bomb_defusal_code[index], bomb_defusal_code_digits[index]);

	Array<int, 3> fill_3 = Array<int, 3>(3);
	for (size_t index = 0; index < 3; index++)
		test_expect(fill_3[index], 3);

	Array_init(double, gen_consts, { 3.1415, 2.7182, 1.414, 1.6180 });

	for (size_t index = 0; index < gen_consts.length(); index++)
		test_expect(gen_consts[index], Array_init_gen_consts[index]);

	int fibonacci[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	auto array_fibonacci = CStyleToArray(fibonacci);
	for (size_t index = 0; index < array_fibonacci.length(); index++)
		test_expect(array_fibonacci[index], fibonacci[index]);
}

test_function(Array_GeneralIteratorTest)
{
	Array<int, 7> bomb_defusal_code = { 7, 3, 5, 5, 6, 0, 8 };

	auto iterable = GeneralIterable<Collection<int>, GeneralIterator<Collection<int>, int&>>(bomb_defusal_code, 0, 7);

	size_t expectedIndex = 0;
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
	for (auto digit : Enumerate(bomb_defusal_code))
	{
		test_expect(digit.defaulted, false);
		test_expect(digit.index, expectedIndex);
		test_expect(digit, bomb_defusal_code_digits[expectedIndex]);
		expectedIndex++;
	}
}

add_test(Array_instantiation_test);
add_test(Array_GeneralIteratorTest);