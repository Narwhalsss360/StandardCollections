#ifndef Iterators_h
#define Iterators_h

#include "CollectionDeclarations.h"

#pragma warning(disable: 4309)

#pragma region Iterators
#pragma region GeneralIterator
template <typename CollectionType, typename DereferenceType>
GeneralIterator<CollectionType, DereferenceType>::GeneralIterator(CollectionType* const collection, const index_t index)
	: m_Collection(collection), m_CurrentIndex(index)
{

}

template <typename CollectionType, typename DereferenceType>
bool GeneralIterator<CollectionType, DereferenceType>::operator!=(GeneralIterator& other)
{
	return m_CurrentIndex != other.m_CurrentIndex;
}

template <typename CollectionType, typename DereferenceType>
void GeneralIterator<CollectionType, DereferenceType>::operator++()
{
	m_CurrentIndex++;
}

template <typename CollectionType, typename DereferenceType>
DereferenceType GeneralIterator<CollectionType, DereferenceType>::operator*()
{
	return (*m_Collection)[m_CurrentIndex];
}

template <typename CollectionType, typename DereferenceType>
index_t GeneralIterator<CollectionType, DereferenceType>::index()
{
	return m_CurrentIndex;
}
#pragma endregion

#pragma region Enumeration
template <typename ValueType>
Enumeration<ValueType>::Enumeration(ValueType value)
	: DereferencedIteration(true), value(value), index(SIZE_MAX)
{
}

template <typename ValueType>
Enumeration<ValueType>::Enumeration(ValueType value, index_t index)
	: DereferencedIteration(false), value(value), index(index)
{
}

template <typename ValueType>
Enumeration<ValueType>::operator ValueType&()
{
	return value;
}
#pragma endregion

#pragma region EnumerationIterator
template <typename CollectionType, typename ValueType>
EnumerationIterator<CollectionType, ValueType>::EnumerationIterator(CollectionType* const collection, const index_t index)
	: GeneralIterator<CollectionType, Enumeration<ValueType>>(collection, index)
{
}

template <typename CollectionType, typename ValueType>
Enumeration<ValueType> EnumerationIterator<CollectionType, ValueType>::operator*()
{
	return Enumeration<ValueType>((*(this->m_Collection))[this->m_CurrentIndex], this->m_CurrentIndex);
}
#pragma endregion

#pragma region Zipping
template <typename Zipped1ValueType, typename Zipped2ValueType>
Zipping<Zipped1ValueType, Zipped2ValueType>::Zipping(Zipped1ValueType value1)
	: DereferencedIteration(true), value1(value1), value2(value1), index(SIZE_MAX)
{
}

template <typename Zipped1ValueType, typename Zipped2ValueType>
Zipping<Zipped1ValueType, Zipped2ValueType>::Zipping(Zipped1ValueType value1, Zipped2ValueType value2, const index_t index)
	: DereferencedIteration(false), value1(value1), value2(value2), index(index)
{
}
#pragma endregion

#pragma region ZipIterator
template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>::ZipIterator(CollectionType* const collection, const index_t index)
	: GeneralIterator<CollectionType, Zipping<Zipped1ValueType, Zipped2ValueType>>(collection, index), m_Defaulted(true), m_Collection2(nullptr)
{
}

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>::ZipIterator(CollectionType* const collection, Collection2Type* const collection2, const index_t index)
	: GeneralIterator<CollectionType, Zipping<Zipped1ValueType, Zipped2ValueType>>(collection, index), m_Defaulted(false), m_Collection2(collection2)
{
}

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
Zipping<Zipped1ValueType, Zipped2ValueType> ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>::operator*()
{
	return Zipping<Zipped1ValueType, Zipped2ValueType>((*(this->m_Collection))[this->m_CurrentIndex], (*m_Collection2)[this->m_CurrentIndex], this->m_CurrentIndex);
}
#pragma endregion
#pragma endregion

#pragma region Iterables
#pragma region GeneralIterable
template <typename CollectionType, typename Iterator>
GeneralIterable<CollectionType, Iterator>::GeneralIterable(CollectionType* const collection, const index_t beginIndex, const index_t endIndex)
	: m_Collection(collection), m_BeginIndex(beginIndex), m_EndIndex(endIndex)
{
}

template <typename CollectionType, typename Iterator>
Iterator GeneralIterable<CollectionType, Iterator>::begin() const
{
	return Iterator(m_Collection, m_BeginIndex);
}

template <typename CollectionType, typename Iterator>
Iterator GeneralIterable<CollectionType, Iterator>::end() const
{
	return Iterator(m_Collection, m_EndIndex);
}
#pragma endregion

#pragma region GeneralIteratorWrapper
template <typename Iterator>
GeneralIteratorWrapper<Iterator>::GeneralIteratorWrapper(Iterator begin, Iterator end)
	: m_Begin(begin), m_End(end)
{
}

template <typename Iterator>
Iterator GeneralIteratorWrapper<Iterator>::begin() const
{
	return m_Begin;
}

template <typename Iterator>
Iterator GeneralIteratorWrapper<Iterator>::end() const
{
	return m_End;
}
#pragma endregion

#pragma region ZipIterable
template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
ZipIterable<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>::ZipIterable(CollectionType* const collection, Collection2Type* const collection2, const index_t beginIndex, const index_t endIndex)
	: GeneralIterable<CollectionType, ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>>(collection, beginIndex, endIndex), m_Collection2(collection2)
{
}

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> ZipIterable<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>::begin() const
{
	return ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>(this->m_Collection, m_Collection2, this->m_BeginIndex);
}

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> ZipIterable<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>::end() const
{
	return ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>(this->m_Collection, m_Collection2, this->m_EndIndex);
}
#pragma endregion
#pragma endregion

#endif // !Iterators_h