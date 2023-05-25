#ifndef Collection_h
#define Collection_h

#include "CollectionDefenitions.h"
#include "Iterators.h"

template <typename ValueType>
struct IndexValuePair
{
	ValueType& value;
	const find_index_t index;
	const bool valid;

	IndexValuePair()
		: value(nullref(ValueType)), index(SIZE_MAX), valid(false)
	{
	}

	IndexValuePair(ValueType& value, find_index_t index, bool valid = false)
		: value(value), index(index), valid(valid)
	{
	}

	operator ValueType&()
	{
		return value;
	}
};

template <typename CollectableType>
class Collection
{
public:
	virtual inline index_t Length() const
	{
		return 0;
	}

	virtual inline CollectableType& operator[](index_t) = 0;

	virtual inline const CollectableType& operator[](index_t) const = 0;

	virtual inline GeneralIterator<const Collection<CollectableType>, const CollectableType&> begin() const
	{
		return GeneralIterator<const Collection<CollectableType>, const CollectableType&>(*this, 0);
	}

	virtual inline GeneralIterator<const Collection<CollectableType>, const CollectableType&> end() const
	{
		return GeneralIterator<const Collection<CollectableType>, const CollectableType&>(*this, Length());
	}

	virtual inline GeneralIterator<Collection<CollectableType>, CollectableType&> begin()
	{
		return GeneralIterator<Collection<CollectableType>, CollectableType&>(*this, 0);
	}

	virtual inline GeneralIterator<Collection<CollectableType>, CollectableType&> end()
	{
		return GeneralIterator<Collection<CollectableType>, CollectableType&>(*this, Length());
	}

	virtual inline void Fill(const CollectableType& value)
	{
		for (index_t index = 0; index < this->Length(); index++)
			this->operator[](index) = value;
	}

	virtual inline void Fill(const CollectableType&& value)
	{
		for (index_t index = 0; index < this->Length(); index++)
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
		return this->operator[](this->Length() - 1);
	}

	virtual inline const CollectableType& Last() const
	{
		return this->operator[](this->Length() - 1);
	}

	virtual inline void ForEach(ForEachIteratorPointer(const CollectableType, iterator))
	{
		for (index_t index = 0; index < Length(); ++index)
			iterator(index, this->operator[](index));
	}

	virtual inline void ForEach(ConstForEachIteratorPointer(const CollectableType, iterator)) const
	{
		for (index_t index = 0; index < Length(); ++index)
			iterator(index, this->operator[](index));
	}

	virtual inline IndexValuePair<const CollectableType> Find(const CollectableType& value) const
	{
		for (find_index_t index = 0; index < this->Length(); index++)
			if (this->operator[](index) == value) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
		return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
	}

	virtual inline IndexValuePair<const CollectableType> Find(const CollectableType&& value) const
	{
		for (find_index_t index = 0; index < this->Length(); index++)
			if (this->operator[](index) == value) return IndexValuePair<const CollectableType>(this->operator[](index), index);
		return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
	}

	virtual inline IndexValuePair<const CollectableType> Find(ComparatorFunctionPointer(const CollectableType, comparator)) const
	{
		for (find_index_t index = 0; index < this->Length(); index++)
			if (comparator(this->operator[](index))) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
		return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
	}

	virtual inline IndexValuePair<const CollectableType> FindLast(const CollectableType& value) const
	{
		for (find_index_t index = this->Length() - 1; index >= 0; index--)
			if (this->operator[](index) == value) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
		return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
	}

	virtual inline IndexValuePair<const CollectableType> FindLast(const CollectableType&& value) const
	{
		for (find_index_t index = this->Length() - 1; index >= 0; index--)
			if (this->operator[](index) == value) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
		return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
	}

	virtual inline IndexValuePair<const CollectableType> FindLast(ComparatorFunctionPointer(const CollectableType, comparator)) const
	{
		for (find_index_t index = this->Length() - 1; index >= 0; index--)
			if (comparator(this->operator[](index))) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
		return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
	}
};

inline index_t SafeIndex(index_t tryIndex, index_t collectionLength)
{
	return safe_index(tryIndex, collectionLength);
}

template <typename CStyleArrayType, index_t Length = sizeof(CStyleArrayType)>
inline constexpr void FillCStyleArray(CStyleArrayType(&array)[Length], CStyleArrayType fillValue)
{
	static_array_fill(array, Length, fillValue);
}

template <typename CStyleArrayType, index_t Length = sizeof(CStyleArrayType)>
inline constexpr index_t CStyleLength(CStyleArrayType(&array)[Length])
{
	return Length;
}

#endif // !Collection_h