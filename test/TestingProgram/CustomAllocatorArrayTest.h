#pragma once
#include "Commons.h"
#include "src/CustomAllocatorArray.h"

int* allocated = nullptr;

test_function(alloch_ctor_test)
{
	allocated = alloch_ctor<int>();
	*allocated = 32;
}

test_function(freeh_dtor_test)
{
	freeh_dtor(allocated);
}

test_function(custom_allocator_array)
{
	CustomAllocatorArray<int, alloch_ctor, freeh_dtor> intArray = CustomAllocatorArray<int, alloch_ctor, freeh_dtor>();
	intArray.Push(0);
	test_expect(intArray[0], 0);
	test_expect(intArray[0], 0);
	for (const auto& i : Enumerate((const CustomAllocatorArray<int, alloch_ctor, freeh_dtor>)intArray))
	{
		i.index;
		i.value;
	}
}