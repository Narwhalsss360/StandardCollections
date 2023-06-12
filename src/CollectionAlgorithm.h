#ifndef CollectionAlgorithm_h
#define CollectionAlgorithm_h

#include "CollectionDeclarations.h"
#include "Collection.h"
#include "DynamicArray.h"

namespace CollectionAlgorithm
{
	#pragma region General Operations
	//Shift left, and right.
	template <typename CollectableType>
	void Swap(Collection<CollectableType>& collection, index_t a, index_t b, bool safe = true)
	{
		if (safe)
			if (a >= collection.Length() || b >= collection.Length())
				return;

		CollectableType aCopy = collection[a];
		collection[a] = collection[b];
		collection[b] = aCopy;
	}

	template <typename CollectableType>
	void Reverse(Collection<CollectableType>& collection)
	{
		index_t len = collection.Length();
		if (len <= 1)
			return;


		for (index_t iLeft = 0, iRight = len - 1;
			iLeft < int(len / 2);
			iLeft++, iRight--)
		{
			Swap(collection, iLeft, iRight, false);
		}
	}

	template <typename CollectableType>
	DynamicArray<CollectableType> unique(Collection<CollectableType>& collection)
	{
		DynamicArray<CollectableType> uniqueItems = DynamicArray<CollectableType>();

		for (CollectableType& item : Iterate(collection))
			if (uniqueItems.Find(item).index == -1)
				uniqueItems.Push(item);

		return uniqueItems;
	}
	#pragma endregion

	#pragma region Sorting
	template <typename CollectableType>
	void BubbleSort(Collection<CollectableType>& collection)
	{
		index_t len = collection.Length();
		if (len <= 1)
			return;

		for (index_t iCollection = 0; iCollection < len; iCollection++)
			for (index_t iItemA = 0, iItemB = 1; iItemA < len - iCollection - 1; iItemA++, iItemB++)
				if (collection[iItemA] > collection[iItemB])
					Swap(collection, iItemA, iItemB, false);
	}
	#pragma endregion

	#pragma region Math
	template <typename CollectableType>
	IndexValuePair<CollectableType> Min(Collection<CollectableType>& collection)
	{
		index_t len = collection.Length();
		if (len == 0)
			return IndexValuePair<CollectableType>(nullref(CollectableType), -1, false);
		if (len == 1)
			return IndexValuePair<CollectableType>(collection[0], 0, true);

		index_t leastIndex = 0;
		CollectableType& leastValue = collection[0];

		for (auto enumeration : Enumerate(collection))
			if (enumeration.value < leastValue)
			{
				leastIndex = enumeration.index;
				leastValue = enumeration.value;
			}
		return IndexValuePair<CollectableType>(leastValue, leastIndex, true);
	}

	template <typename CollectableType>
	IndexValuePair<CollectableType> Max(Collection<CollectableType>& collection)
	{
		index_t len = collection.Length();
		if (len == 0)
			return IndexValuePair<CollectableType>(nullref(CollectableType), -1, false);
		if (len == 1)
			return IndexValuePair<CollectableType>(collection[0], 0, true);

		index_t leastIndex = 0;
		CollectableType& leastValue = collection[0];

		for (auto enumeration : Enumerate(collection))
			if (enumeration.value > leastValue)
			{
				leastIndex = enumeration.index;
				leastValue = enumeration.value;
			}
		return IndexValuePair<CollectableType>(leastValue, leastIndex, true);
	}

	template <typename CollectableType>
	CollectableType Sum(Collection<CollectableType>& collection)
	{
		CollectableType sum = 0;
		for (CollectableType& number : Iterate(collection))
			sum += number;
		return sum;
	}

	template <typename CollectableType>
	CollectableType Product(Collection<CollectableType>& collection)
	{
		CollectableType productResult = 1;
		for (CollectableType& number : Iterate(collection))
			productResult *= number;
		return productResult;
	}

	template <typename CollectableType>
	CollectableType Average(Collection<CollectableType>& collection)
	{
		if (collection.Length() == 0)
			return 0;
		return (Sum(collection) / collection.Length());
	}

	template <typename CollectableType>
	CollectableType Median(Collection<CollectableType>& collection)
	{
		index_t len = collection.Length();
		if (len == 0)
			return 0;
		if (len == 1)
			return collection[0];

		if (len % 2 != 0)
			return collection[len / 2];
		return (collection[len / 2] + collection[(len / 2) - 1]) / 2;
	}

	template <typename CollectableType>
	DynamicArray<Array<CollectableType, 2>> Factors(CollectableType number)
	{
		auto factors = DynamicArray<Array<CollectableType, 2>>();

		if (number != 0)
			for (CollectableType n = 1; n <= number; n++)
				if (number % n == 0)
					factors.Push({ n, number / n });

		return factors;
	}
	#pragma region Statistics
	#pragma endregion
	#pragma endregion
}
#endif