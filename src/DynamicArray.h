#ifndef DynamicArray_h
#define DynamicArray_h

#include "DynamicCollection.h"
#ifdef initializer_list_supported
#include <initializer_list>
#endif // initializer_list_supported

template <typename CollectableType>
DynamicArray<CollectableType>::DynamicArray()
	: m_Array(nullptr), m_Capacity(0),  m_Length(0)
{
}

template <typename CollectableType>
DynamicArray<CollectableType>::DynamicArray(DynamicArray<CollectableType>& other)
	: m_Array(nullptr), m_Capacity(0), m_Length(0)
{
	operator=(other);
}

template <typename CollectableType>
DynamicArray<CollectableType>::DynamicArray(DynamicArray<CollectableType>&& other)
	: m_Array(nullptr), m_Capacity(0), m_Length(0)
{
	this->operator=(other);
}

#ifdef initializer_list_supported
template <typename CollectableType>
DynamicArray<CollectableType>::DynamicArray(const std::initializer_list<CollectableType>& initializers)
	: m_Array(nullptr), m_Capacity(0), m_Length(0)
{
	this->operator=(initializers);
}
#endif // initializer_list_supported

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
DynamicArray<CollectableType>& DynamicArray<CollectableType>::operator=(const DynamicArray<CollectableType>& other)
{
	SetCapacity(other.Length());
	SetLength(other.Length());

	for (index_t i = 0; i < other.Length(); i++)
		this->operator[](i) = other.operator[](i);

	return *this;
}

template <typename CollectableType>
DynamicArray<CollectableType>& DynamicArray<CollectableType>::operator=(const DynamicArray<CollectableType>&& other)
{
	SetCapacity(other.Length());
	SetLength(other.Length());
	for (index_t i = 0; i < other.Length(); i++)
		this->operator[](i) = other.operator[](i);

	other.SetCapacity(0);
	return *this;
}

#ifdef initializer_list_supported
template <typename CollectableType>
DynamicArray<CollectableType>& DynamicArray<CollectableType>::operator=(const std::initializer_list<CollectableType>& initializers)
{
	this->SetCapacity(initializers.size());

	const CollectableType* const initializerArray = initializers.begin();

	for (index_t index = 0; index < initializers.size(); index++)
		this->operator[](index) = initializerArray[index];

	return *this;
}
#endif // initializer_list_supported

template <typename CollectableType>
void DynamicArray<CollectableType>::SetLength(index_t newLength)
{
	if (newLength > m_Capacity)
		SetCapacity(newLength);
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