#ifndef CollectionAlgorithm_h
#define CollectionAlgorithm_h

#include "CollectionDeclarations.h"
#include "Collection.h"
#include "DynamicArray.h"

namespace CollectionAlgorithm
{
#pragma region Argument Constant Expressions
	constexpr bool SortOrderReversed = true;
	constexpr bool SortOrderNormal = true;
#pragma endregion

	#pragma region General Operations
	//Shift left, and right.
	template <typename CollectableType>
	void Swap(Collection<CollectableType>& collection, index_t a, index_t b, bool safe = true)
	{
		if (safe)
			if (a >= collection.Length() || b >= collection.Length())
				return;

		if (a == b)
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

#pragma region List Operations
	template <typename CollectableType>
	DynamicArray<CollectableType> Union(Collection<CollectableType>& collectionA, Collection<CollectableType>& collectionB)
	{
		DynamicArray<CollectableType> unionItems = DynamicArray<CollectableType>();
		for (auto& item : collectionA)
					unionItems += item;
		for (auto& item : collectionB)
			if (unionItems.Find(item).index == -1)
				unionItems += item;
		return unionItems;
	}

	template <typename CollectableType>
	DynamicArray<CollectableType> Intersection(Collection<CollectableType>& collectionA, Collection<CollectableType>& collectionB)
	{
		DynamicArray<CollectableType> intersectionItems = DynamicArray<CollectableType>();
		for (auto& item : collectionA)
			if (collectionB.Find(item).index != -1)
				intersectionItems += item;
		return intersectionItems;
	}
#pragma endregion

	#pragma region Sorting
	template <typename CollectableType>
	void BubbleSort(Collection<CollectableType>& collection, bool reverse = false)
	{
		index_t len = collection.Length();
		if (len <= 1)
			return;

		for (index_t iCollection = 0; iCollection < len; iCollection++)
			for (index_t iItemA = 0, iItemB = 1; iItemA < len - iCollection - 1; iItemA++, iItemB++)
				if (reverse ? collection[iItemA] < collection[iItemB] : collection[iItemA] > collection[iItemB])
					Swap(collection, iItemA, iItemB, false);
	}

	template <typename CollectableType>
	void SelectionSort(Collection<CollectableType>& collection, bool reverse = false)
	{
		index_t len = collection.Length();

		for (index_t iLowest = 0; iLowest < len; iLowest++)
			for (index_t iItem = iLowest + 1; iItem < len; iItem++)
				if (collection[iItem] < collection[iLowest])
					Swap(collection, iItem, iLowest);
	}

	template <typename CollectableType>
	void InsertionSort(Collection<CollectableType>& collection, bool reverse = false)
	{
		index_t len = collection.Length();
		for (index_t iCollection = 0; iCollection < len; iCollection++)
			for (index_t iItemA = iCollection, iItemB = iCollection - 1; iItemA >= 1; iItemA--, iItemB--)
				if (reverse ? collection[iItemA] > collection[iItemB] : collection[iItemA] < collection[iItemB])
					Swap(collection, iItemA - 1, iItemA);
	}

	template <typename CollectableType>
	void Sort(Collection<CollectableType>& collection, void (*sorter)(Collection<CollectableType>&, bool), bool reverse = false)
	{
		sorter(collection, reverse);
	}
	#pragma endregion

	#pragma region Math
	template <typename CollectableType>
	IndexValuePair<CollectableType> Min(Collection<CollectableType>& collection)
	{
		index_t len = collection.Length();
		if (len == 0)
			return IndexValuePair<CollectableType>(nullptr, -1, false);
		if (len == 1)
			return IndexValuePair<CollectableType>(&collection[0], 0, true);

		index_t leastIndex = 0;
		CollectableType& leastValue = collection[0];

		for (auto enumeration : Enumerate(collection))
			if (enumeration.value < leastValue)
			{
				leastIndex = enumeration.index;
				leastValue = enumeration.value;
			}
		return IndexValuePair<CollectableType>(&leastValue, leastIndex, true);
	}

	template <typename CollectableType>
	IndexValuePair<CollectableType> Max(Collection<CollectableType>& collection)
	{
		index_t len = collection.Length();
		if (len == 0)
			return IndexValuePair<CollectableType>(nullptr, -1, false);
		if (len == 1)
			return IndexValuePair<CollectableType>(&collection[0], 0, true);

		index_t leastIndex = 0;
		CollectableType& leastValue = collection[0];

		for (auto enumeration : Enumerate(collection))
			if (enumeration.value > leastValue)
			{
				leastIndex = enumeration.index;
				leastValue = enumeration.value;
			}
		return IndexValuePair<CollectableType>(&leastValue, leastIndex, true);
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

	template <typename CollectableType>
	DynamicArray<CollectableType> PrimeFactors(CollectableType number)
	{
		DynamicArray<CollectableType> primeFactors = DynamicArray<CollectableType>();
		CollectableType divisor = 2;

		number = abs(number);

		while (number > 1)
		{
			if (number % divisor == 0)
			{
				primeFactors += divisor;
				number /= divisor;
				continue;
			}
			divisor++;
		}

		return primeFactors;
	}

	template <typename CollectableType>
	CollectableType LCM(Collection<CollectableType>& collection)
	{
		auto primesWithExponents = DynamicArray<Array<int, 2>>();
		for (CollectableType& number : collection)
		{
			DynamicArray<CollectableType> primeFactors = PrimeFactors(number);
			for (auto& factor : primeFactors)
			{
				find_index_t indexOfPair = -1;
				for (auto enumeration : Enumerate(primesWithExponents))
				{
					if (enumeration.value[0] == factor)
					{
						indexOfPair = enumeration.index;
						break;
					}
				}

				if (indexOfPair == -1)
				{
					Array<int, 2> factorWithExponent = Array<int, 2>();
					factorWithExponent[0] = factor;
					factorWithExponent[1] = 1;
					primesWithExponents.Push(factorWithExponent);
				}
				else
				{
					index_t countOfFactor = primeFactors.Count(factor);
					if (countOfFactor > primesWithExponents[indexOfPair][1])
						primesWithExponents[indexOfPair][1] = countOfFactor;
				}
			}
		}

		CollectableType lcm = 1;
		for (auto& factorWithExponent : primesWithExponents)
			lcm *= pow(factorWithExponent[0], factorWithExponent[1]);

		return lcm;
	}

	template <typename CollectableType>
	CollectableType GCD(Collection<CollectableType>& collection)
	{
		return Product(collection) / LCM(collection);
	}
	#pragma region Statistics
	template <typename CollectableType>
	CollectableType StandardDeviation(Collection<CollectableType>& collection, bool population = false)
	{
		CollectableType summation = 0;
		CollectableType average = Average(collection);
		for (auto& number : collection)
			summation += pow(number - average, 2);
		return sqrt(summation / (population ? collection.Length() : collection.Length() - 1));
	}
	#pragma endregion
	#pragma endregion
}
#endif