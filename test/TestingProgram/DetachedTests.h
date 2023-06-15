#pragma once
#include "Commons.h"

template <typename CollectionType, typename ReturnType>
ReturnType GetSumOfCollection(const CollectionType* const collection, size_t size = sizeof(CollectionType))
{
	ReturnType sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += (*collection)[i];
	return sum;
}

template <typename CollectionType, typename DereferenceType>
class NewGeneralIterator
{
public:
	NewGeneralIterator(const CollectionType* const collection, const index_t index)
		: m_Collection(collection), m_CurrentIndex(index)
	{
	}

	virtual bool operator!=(NewGeneralIterator& other)
	{
		return m_CurrentIndex != other.m_CurrentIndex;
	}

	virtual void operator++()
	{
		m_CurrentIndex++;
	}

	virtual DereferenceType operator*()
	{
		return (*m_Collection)[m_CurrentIndex];
	}

	virtual index_t index()
	{
		return m_CurrentIndex;
	}

protected:
	const CollectionType* const m_Collection;
	index_t m_CurrentIndex;
};

template <typename CollectionType, typename Iterator>
class NewGeneralIterable
{
public:
	NewGeneralIterable(const CollectionType* const collection, const index_t beginIndex, const index_t endIndex)
		: m_Collection(collection), m_BeginIndex(beginIndex), m_EndIndex(endIndex)
	{
	}

	virtual Iterator begin() const
	{
		return Iterator(m_Collection, m_BeginIndex);
	}

	virtual Iterator end() const
	{
		return Iterator(m_Collection, m_EndIndex);
	}

protected:
	const CollectionType* const m_Collection;
	const index_t m_BeginIndex, m_EndIndex;
};
 
template <typename CollectableType>
NewGeneralIterable<Collection<CollectableType>, NewGeneralIterator<Collection<CollectableType>, CollectableType>> NewIterate(const Collection<CollectableType>& collection)
{
	return NewGeneralIterable<Collection<CollectableType>, NewGeneralIterator<Collection<CollectableType>, CollectableType>>(&collection, 0, collection.Length());
}

void PointersToAnyTypeOfCollection()
{
	Array<int, 3> CollectionArray = { 1, 2, 3 };
	int sCollectionArray = GetSumOfCollection<Array<int, 3>, int>(&CollectionArray, 3);

	const int CArray[3] = { 1, 2, 3 };
	int sCArray = GetSumOfCollection<int[3], int>(&CArray, 3);
}

void NewIterators()
{
	Array<int, 3> CollectionArray = { 1, 2, 3 };
	const int CArray[3] = { 1, 2, 3 };

	for (auto begin = NewGeneralIterator<Array<int, 3>, int>(&CollectionArray, 0),
		end = NewGeneralIterator<Array<int, 3>, int>(&CollectionArray, CollectionLength(CollectionArray));
		begin != end;
		++begin)
	{
		auto i = *begin;
		{
			std::cout << i << ' ';
		}
	}
	std::cout << '\n';

	auto iterable = Iterate(CollectionArray);
	for (auto& i : iterable)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';
}

void RunDetachedTests()
{
	std::cout << "Running detached tests...\n";
	PointersToAnyTypeOfCollection();
	NewIterators();
}