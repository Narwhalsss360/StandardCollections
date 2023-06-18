#pragma once
#include "Commons.h"

template <typename T>
T* alloc_h(size_t count)
{
	return (T*)malloc(sizeof(T) * count);
}

template <typename T>
void free_h(T* h_ptr)
{
	free(h_ptr);
}

template <typename T>
T* ctor_alloc_h(size_t count)
{
	return new T[count];
}

template <typename T>
void ctor_free_h(T* h_ptr)
{
	delete[] h_ptr;
}

template <typename CollectableType, CollectableType* (*Allocator)(size_t) = ctor_alloc_h, void (*Freer)(CollectableType*) = ctor_free_h>
class NewDynamicArray : public DynamicCollection<CollectableType>
{
public:
	NewDynamicArray()
	{
	}

	virtual inline index_t Capacity() const
	{
		return cap;
	}

	virtual inline void SetCapacity(index_t newCapacity)
	{
	retry:
		if (arr == nullptr)
		{
			arr = Allocator(newCapacity);
			if (arr != nullptr)
				cap = newCapacity;
			return;
		}

		CollectableType* newAllocation = Allocator(newCapacity);
		if (newAllocation == nullptr)
			goto retry;

		for (index_t index = 0; index < (newCapacity < len ? newCapacity : len); index++)
			newAllocation[index] = arr[index];

		Freer(arr);
		arr = newAllocation;

		cap = newCapacity;
		len = newCapacity < len ? newCapacity : len;
	}

	virtual inline index_t Length() const
	{
		return len;
	}

	virtual inline void SetLength(index_t newLength)
	{
		if (newLength > cap)
			SetCapacity(newLength);
		len = newLength;
	}

	virtual inline CollectableType& operator[](index_t index)
	{
		return arr[SafeIndex(index, len)];
	}

	virtual inline const CollectableType& operator[](index_t index) const
	{
		return arr[SafeIndex(index, len)];
	}

	CollectableType* arr = nullptr;
	index_t cap = 0, len = 0;
};

template <typename T>
T* alloc_s(size_t count)
{
	return (T*)_malloca(sizeof(T) * count);
}

template <typename T>
void free_s(T* ptr)
{
	_freea(ptr);
}

struct MathFunctionPair
{
	MathFunctionPair()
		: x(0), y(0)
	{
	}

	MathFunctionPair(double x, double y)
		: x(x), y(y)
	{
	}

	bool operator==(const MathFunctionPair& other) const
	{
		return x == other.x && y == other.y;
	}

	double x, y;
};

NewDynamicArray<MathFunctionPair, alloc_s, free_s> fpairArray;
void newDynamicArrayTest()
{
	int n = 2;
	fpairArray.Push(MathFunctionPair(0, pow(0, 2)));
	fpairArray.Push(MathFunctionPair(1, pow(1, 2)));
	fpairArray.Push(MathFunctionPair(2, pow(2, 2)));
	fpairArray.Push(MathFunctionPair(3, pow(3, 2)));
	fpairArray.Push(MathFunctionPair(4, pow(4, 2)));
}

void otherFunction()
{
	for (auto& i : fpairArray)
		std::cout << i.x;
	fpairArray.Remove(0);
}

void RunDetachedTests()
{
	std::cout << "Running detached tests...\n";
	newDynamicArrayTest();
	otherFunction();
}