#pragma once
#include "TestProvider.h"
#include "src/StandardCollections.h"

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

struct ContainerA
{
	ContainerA()
		: number(0)
	{
	}

	ContainerA(int n)
		: number(n)
	{
	}

	int number;

	bool operator==(const ContainerA& other) const
	{
		return number == other.number;
	}
};

struct ContainerB
{
	ContainerB()
		: precision(0.0f)
	{
	}

	ContainerB(float p)
		: precision(p)
	{
	}

	float precision;

	bool operator==(const ContainerB& other) const
	{
		return precision == other.precision;
	}
};

struct ContainerC : ContainerA, ContainerB
{
	ContainerC()
		: ContainerA(), ContainerB(), string("default")
	{
	}

	ContainerC(int n, float p, std::string s)
		: ContainerA(n), ContainerB(p), string(s)
	{
	}

	std::string string;

	bool operator==(const ContainerC& other) const
	{
		return precision == other.precision && number == other.number && string == other.string;
	}
};