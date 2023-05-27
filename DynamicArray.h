#ifndef DynamicArray_h
#define DynamicArray_h

#include "DynamicCollection.h"
#ifdef __cpp_initializer_lists
#include <initializer_list>
#endif // __cpp_initializer_lists

template <typename CollectableType>
DynamicArray<CollectableType>::DynamicArray()
	: m_Array(nullptr), m_Capacity(0),  m_Length(0)
{
}

template <typename CollectableType>
index_t DynamicArray<CollectableType>::Capacity() const
{
	return m_Capacity;
}

template <typename CollectableType>
index_t DynamicArray<CollectableType>::Length() const
{
	return m_Length;
}

template <typename CollectableType>
CollectableType& DynamicArray<CollectableType>::operator[](index_t index)
{
	return m_Array[safe_index(index, m_Length)];
}

template <typename CollectableType>
const CollectableType& DynamicArray<CollectableType>::operator[](index_t index) const
{
	return m_Array[safe_index(index, m_Length)];
}

template <typename CollectableType>
void DynamicArray<CollectableType>::SetLength(index_t newLength)
{
	m_Length = newLength;
}

template <typename CollectableType>
void DynamicArray<CollectableType>::SetCapacity(index_t newCapacity)
{
retry:
	if (m_Array == nullptr)
	{
		m_Array = new CollectableType[newCapacity];
		if (m_Array != nullptr)
			m_Capacity = newCapacity;
		return;
	}

	CollectableType* newAllocation = new CollectableType[newCapacity];
	if (newAllocation == nullptr)
		goto retry;

	for (index_t index = 0; index < (newCapacity < m_Length ? newCapacity : m_Length); index++)
		newAllocation[index] = m_Array[index];

	delete[] m_Array;
	m_Array = newAllocation;

	m_Capacity = newCapacity;
	m_Length = newCapacity < m_Length ? newCapacity : m_Length;
}

template <typename CollectableType>
DynamicArray<CollectableType>::~DynamicArray()
{
	if (m_Array != nullptr)
		delete[] m_Array;

	m_Capacity = 0;
	m_Length = 0;
}
#endif // !DynamicArray_h