#pragma once
#include "TestProvider.h"
#include "StandardCollections.h"

constexpr int bomb_defusal_code_digits[] = { 7, 3, 5, 5, 6, 0, 8 };

enum PrintStyles
{
	PythonStyle,
	Indexed
};

template <typename CollectableType>
void PrintCollection(Collection<CollectableType>& collection, PrintStyles printStyle = PrintStyles::PythonStyle)
{
	switch (printStyle)
	{
	case PythonStyle:
		test_standard_output_write('[');
		for (auto i : Enumerate(collection))
		{
			test_standard_output_write(i.value);
			if (i.index != collection.Length() - 1) test_standard_output_write(", ");
		}
		test_standard_output_write(']');
		break;
	case Indexed:
		for (auto i : Enumerate(collection))
		{
			test_standard_output_write('[');
			test_standard_output_write(i.index);
			test_standard_output_write("]:");
			test_standard_output_write(i.value);
			if (i.index != collection.Length() - 1) test_standard_output_write(", ");
		}
		break;
	default:
		break;
	}
}