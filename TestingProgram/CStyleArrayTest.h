#pragma once
#include "..\StandardCollections.h"
#include "Commons.h"

test_function(c_style_general_iterate)
{
	{ /*Testing general iterate on int array*/

		int bomb_defusal_code[7] = { 7 ,3, 5, 5, 6, 0, 8 };
		{ /*Testing iterators*/

			test_expect(static_array_length(int, bomb_defusal_code), 7);

			auto bomb_defusal_code_begin_general_iterator = GeneralIterator<int[static_array_length(int, bomb_defusal_code)], int&>(bomb_defusal_code, 0);
			auto bomb_defusal_code_end_general_iterator = GeneralIterator<int[static_array_length(int, bomb_defusal_code)], int&>(bomb_defusal_code, static_array_length(int, bomb_defusal_code));
			int expectedIndex = 0;
			for (;
				bomb_defusal_code_begin_general_iterator != bomb_defusal_code_end_general_iterator;
				++bomb_defusal_code_begin_general_iterator)
			{
				test_expect(bomb_defusal_code_begin_general_iterator.operator*(), bomb_defusal_code[expectedIndex]);
				test_expect(bomb_defusal_code_begin_general_iterator.index(), expectedIndex);
				expectedIndex++;
			}
		}

		{ /*Testing iterables*/
			auto bomb_defusal_iterable = GeneralIterable<int[7], GeneralIterator<int[7], int&>>(bomb_defusal_code, 0, 7);

			int expectedIndex = 0;
			for (auto& num : bomb_defusal_iterable)
			{
				test_expect(bomb_defusal_code[expectedIndex], num);
				expectedIndex++;
			}

			expectedIndex = 0;
			for (auto& num : Iterate(bomb_defusal_code))
			{
				test_expect(bomb_defusal_code[expectedIndex], num);
				expectedIndex++;
			}
		}
	}
}

test_function(c_style_enumerate)
{
	int bomb_defusal_code[7] = { 7 ,3, 5, 5, 6, 0, 8 };

	{ /*Testing Iterators*/
		auto enumeration_iterator_begin = EnumerationIterator<int[7], int&>(bomb_defusal_code, 0);
		auto enumeration_iterator_end = EnumerationIterator<int[7], int&>(bomb_defusal_code, 7);

		size_t expectedIndex = 0;
		for (; enumeration_iterator_begin != enumeration_iterator_end;
			++enumeration_iterator_begin)
		{
			test_expect(enumeration_iterator_begin.operator*().index, expectedIndex);
			test_expect(enumeration_iterator_begin.operator*().operator int& (), bomb_defusal_code[expectedIndex]);
			test_expect(enumeration_iterator_begin.index(), expectedIndex);
			expectedIndex++;
		}
	}

	{ /*Testing Iterables*/
		auto enumeration_iterable = GeneralIterable<int[7], EnumerationIterator<int[7], int&>>(bomb_defusal_code, 0, 7);
		size_t expectedIndex = 0;
		for (auto enumeration : enumeration_iterable)
		{
			test_expect(enumeration.defaulted, false);
			test_expect(enumeration.index, expectedIndex);
			test_expect(enumeration.operator int& (), bomb_defusal_code[expectedIndex]);
			expectedIndex++;
		}

		expectedIndex = 0;
		for (auto enumeration : Enumerate(bomb_defusal_code))
		{
			test_expect(enumeration.defaulted, false);
			test_expect(enumeration.index, expectedIndex);
			test_expect(enumeration.operator int& (), bomb_defusal_code[expectedIndex]);
			expectedIndex++;
		}
	}
}

int f(int x)
{
	return (int)pow(x, 2) - 1;
}

test_function(c_style_zip)
{
	int x_values[] = { -2, -1, 0, 1, 2 };
	int y_values[CStyleLength(x_values)];

	FillCStyleArray(y_values, 0);

	/*Setup*/
	for (auto x : Enumerate(x_values))
	{
		test_expect(x.defaulted, false);
		y_values[x.index] = f(x);
	}

	for (size_t index = 0; index < CStyleLength(x_values); index++)
		test_expect(y_values[index], f(x_values[index]));

	{ /*Testing Iterators*/
		auto zip_begin = ZipIterator<int[5], int>(x_values, y_values, 0);
		auto zip_end = ZipIterator<int[5], int>(x_values, y_values, 5);

		test_expect(zip_begin.m_Defaulted, false);
		test_expect(zip_end.m_Defaulted, false);
		size_t expectedIndex = 0;
		for (;
			zip_begin != zip_end;
			++zip_begin)
		{
			test_expect(zip_begin.m_Defaulted, false);
			test_expect(zip_begin.operator*().value1, x_values[zip_begin.operator*().index]);
			test_expect(zip_begin.operator*().value2, y_values[zip_begin.operator*().index]);
			test_expect(zip_begin.operator*().index, expectedIndex);
			expectedIndex++;
		}
	}

	{ /*Testing Iterables*/
		auto zip_iterable = ZipIterable<int[5], int>(x_values, y_values, 0, 5);
		
		size_t expectedIndex = 0;
		for (auto zipping : zip_iterable)
		{
			test_expect(zipping.defaulted, false);
			test_expect(zipping.value1, x_values[zipping.index]);
			test_expect(zipping.value2, y_values[zipping.index]);
			test_expect(zipping.index, expectedIndex);
			expectedIndex++;
		}

		expectedIndex = 0;
		for (auto zipping : Zip(x_values, y_values))
		{
			test_expect(zipping.defaulted, false);
			test_expect(zipping.value1, x_values[zipping.index]);
			test_expect(zipping.value2, y_values[zipping.index]);
			test_expect(zipping.index, expectedIndex);
			expectedIndex++;
		}
	}
}

add_test(c_style_general_iterate);
add_test(c_style_enumerate);
add_test(c_style_zip);