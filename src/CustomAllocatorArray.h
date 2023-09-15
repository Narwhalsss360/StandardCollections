#ifndef CustomAllocatorArray_h
#define CustomAllocatorArray_h

#include "DynamicArray.h"

template <typename T>
T* alloch_ctor(size_t count = 1)
{
	return new T[count];
}

template <typename T>
void freeh_dtor(T* memory)
{
	delete[] memory;
}

template <typename CollectableType, CollectableType* (*Allocator) (size_t), void (*Freer)(CollectableType*)>
class CustomAllocatorArray : public DynamicArray<CollectableType>
{
public:
	CustomAllocatorArray()
		: DynamicArray<CollectableType>()
	{
	}

	CustomAllocatorArray(const CustomAllocatorArray<CollectableType, Allocator, Freer>& other)
		: DynamicArray<CollectableType>(other)
	{
	}

	CustomAllocatorArray(const Collection<CollectableType>& other)
		: DynamicArray<CollectableType>(other)
	{
	}

	inline void SetCapacity(index_t newCapacity) override
	{
	retry:
		if (this->m_Array == nullptr)
		{
			this->m_Array = Allocator(newCapacity);
			if (this->m_Array != nullptr)
				this->m_Capacity = newCapacity;
			return;
		}

		CollectableType* newAllocation = Allocator(newCapacity);
		if (newAllocation == nullptr)
			goto retry;

		for (index_t index = 0; index < (newCapacity < this->m_Length ? newCapacity : this->m_Length); index++)
			newAllocation[index] = this->m_Array[index];

		Freer(this->m_Array);
		this->m_Array = newAllocation;

		this->m_Capacity = newCapacity;
		this->m_Length = newCapacity < this->m_Length ? newCapacity : this->m_Length;
	}

	~CustomAllocatorArray()
	{
		if (this->m_Array != nullptr)
			Freer(this->m_Array);

		this->m_Array = nullptr;

		this->m_Capacity = 0;
		this->m_Length = 0;
	}
};

#endif