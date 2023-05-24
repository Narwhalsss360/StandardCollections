#ifndef Collection_h
#define Collection_h

#define safe_index(index, length) (index % length)
#define static_array_length(type, identifier) (sizeof(identifier) / sizeof(type))
#define static_array_fill(identifier, length, value) for (size_t index_##identifier = 0; index_##identifier < length; ++index_##identifier) identifier[index_##identifier] = value

#define ComparatorFunction(type, name) bool name(type& item)
#define ComparatorFunctionPointer(type, name) bool (*name)(type&)

#include "Iterators.h"

template <typename ValueType>
struct IndexValuePair
{
	ValueType& value;
	size_t index;

	IndexValuePair(ValueType& value, size_t index)
		: value(value), index(index)
	{
	}

	operator ValueType()
	{
		return value;
	}
};

template <typename CollectableType>
class Collection
{
public:
	virtual inline size_t length() const
	{
		return 0;
	}

	virtual inline CollectableType& operator[](size_t) = 0;

	virtual inline const CollectableType& operator[](size_t) const = 0;

	/* Still Pre-test:
	virtual inline GeneralIterator<Collection<CollectableType>, CollectableType&> begin() const
	{
		return GeneralIterator<Collection<CollectableType>, CollectableType&>(*this, 0);
	}

	virtual inline GeneralIterator<Collection<CollectableType>, CollectableType&> end() const
	{
		return GeneralIterator<Collection<CollectableType>, CollectableType&>(*this, length());
	}

	virtual inline void Fill(CollectableType& value)
	{
		for (size_t index = 0; index < this->length(); index++)
			this->operator[](index) = value;
	}

	virtual inline void Fill(CollectableType&& value)
	{
		for (size_t index = 0; index < this->length(); index++)
			this->operator[](index) = value;
	}

	virtual inline CollectableType& First()
	{
		return this->operator[](0);
	}

	virtual inline const CollectableType& First() const
	{
		return this->operator[](0);
	}

	virtual inline CollectableType& Last()
	{
		return this->operator[](this->length() - 1);
	}

	virtual inline const CollectableType& Last() const
	{
		return this->operator[](this->length() - 1);
	}

	virtual inline void ForEach(ForEachIteratorPointer(CollectableType, iterator))
	{
		for (size_t index = 0; index < length(); ++index)
			iterator(index, this->operator[](index));
	}

	virtual inline void ForEach(ConstForEachIteratorPointer(CollectableType, iterator)) const
	{
		for (size_t index = 0; index < length(); ++index)
			iterator(index, this->operator[](index));
	}

	virtual inline IndexValuePair<CollectableType> Find(CollectableType& value) const
	{
		for (size_t index = 0; index < this->length(); index++)
			if (this->operator[](index) == value) return IndexValuePair<CollectableType>(this->operator[](index), index);
	}

	virtual inline IndexValuePair<CollectableType> Find(CollectableType&& value) const
	{
		for (size_t index = 0; index < this->length(); index++)
			if (this->operator[](index) == value) IndexValuePair<CollectableType>(this->operator[](index), index);
	}

	virtual inline IndexValuePair<CollectableType> Find(ComparatorFunctionPointer(CollectableType, comparator)) const
	{
		for (size_t index = 0; index < this->length(); index++)
			if (comparator(this->operator[](index))) IndexValuePair<CollectableType>(this->operator[](index), index);
	}

	virtual inline IndexValuePair<CollectableType> FindLast(CollectableType& value) const
	{
		for (size_t index = this->length() - 1; index >= 0; index--)
			if (this->operator[](index) == value) IndexValuePair<CollectableType>(this->operator[](index), index);
	}

	virtual inline IndexValuePair<CollectableType> FindLast(CollectableType&& value) const
	{
		for (size_t index = this->length() - 1; index >= 0; index--)
			if (this->operator[](index) == value) IndexValuePair<CollectableType>(this->operator[](index), index);
	}

	virtual inline IndexValuePair<CollectableType> FindLast(ComparatorFunctionPointer(CollectableType, comparator)) const
	{
		for (size_t index = this->length() - 1; index >= 0; index--)
			if (comparator(this->operator[](index))) IndexValuePair<CollectableType>(this->operator[](index), index);
	}
	*/
};

inline size_t SafeIndex(size_t tryIndex, size_t collectionLength)
{
	return safe_index(tryIndex, collectionLength);
}

template <typename CStyleArrayType, size_t Length = sizeof(CStyleArrayType)>
inline constexpr void FillCStyleArray(CStyleArrayType(&array)[Length], CStyleArrayType fillValue)
{
	static_array_fill(array, Length, fillValue);
}

template <typename CStyleArrayType, size_t Length = sizeof(CStyleArrayType)>
inline constexpr size_t CStyleLength(CStyleArrayType(&array)[Length])
{
	return Length;
}

#endif // !Collection_h