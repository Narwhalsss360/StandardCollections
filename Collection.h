#ifndef Collection_h
#define Collection_h

#include "CollectionDeclarations.h"
#include "Iterators.h"

#pragma region IndexValuePair
template <typename ValueType>
IndexValuePair<ValueType>::IndexValuePair()
	: value(nullref(ValueType)), index(SIZE_MAX), valid(false)
{
}
template <typename ValueType>
IndexValuePair<ValueType>::IndexValuePair(ValueType& value, find_index_t index, bool valid)
	: value(value), index(index), valid(valid)
{
}
template <typename ValueType>
IndexValuePair<ValueType>::operator ValueType&()
{
	return value;
}
#pragma endregion

#pragma region Collection
template <typename CollectableType>
index_t Collection<CollectableType>::Length() const
{
	return 0;
}

template <typename CollectableType>
GeneralIterator<const Collection<CollectableType>, const CollectableType&> Collection<CollectableType>::begin() const
{
	return GeneralIterator<const Collection<CollectableType>, const CollectableType&>(*this, 0);
}

template <typename CollectableType>
GeneralIterator<const Collection<CollectableType>, const CollectableType&> Collection<CollectableType>::end() const
{
	return GeneralIterator<const Collection<CollectableType>, const CollectableType&>(*this, Length());
}

template <typename CollectableType>
GeneralIterator<Collection<CollectableType>, CollectableType&> Collection<CollectableType>::begin()
{
	return GeneralIterator<Collection<CollectableType>, CollectableType&>(*this, 0);
}

template <typename CollectableType>
GeneralIterator<Collection<CollectableType>, CollectableType&> Collection<CollectableType>::end()
{
	return GeneralIterator<Collection<CollectableType>, CollectableType&>(*this, Length());
}

template <typename CollectableType>
void Collection<CollectableType>::Fill(const CollectableType& value)
{
	for (index_t index = 0; index < this->Length(); index++)
		this->operator[](index) = value;
}

template <typename CollectableType>
void Collection<CollectableType>::Fill(const CollectableType&& value)
{
	for (index_t index = 0; index < this->Length(); index++)
		this->operator[](index) = value;
}

template <typename CollectableType>
CollectableType& Collection<CollectableType>::First()
{
	return this->operator[](0);
}

template <typename CollectableType>
const CollectableType& Collection<CollectableType>::First() const
{
	return this->operator[](0);
}

template <typename CollectableType>
CollectableType& Collection<CollectableType>::Last()
{
	return this->operator[](this->Length() - 1);
}

template <typename CollectableType>
const CollectableType& Collection<CollectableType>::Last() const
{
	return this->operator[](this->Length() - 1);
}

template <typename CollectableType>
void Collection<CollectableType>::ForEach(ForEachIteratorPointer(CollectableType, iterator))
{
	for (index_t index = 0; index < Length(); ++index)
		iterator(index, this->operator[](index));
}

template <typename CollectableType>
void Collection<CollectableType>::ForEach(ConstForEachIteratorPointer(const CollectableType, iterator)) const
{
	for (index_t index = 0; index < Length(); ++index)
		iterator(index, this->operator[](index));
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::Find(const CollectableType& value) const
{
	for (find_index_t index = 0; index < this->Length(); index++)
		if (this->operator[](index) == value) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
	return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::Find(const CollectableType&& value) const
{
	for (find_index_t index = 0; index < this->Length(); index++)
		if (this->operator[](index) == value) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
	return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::Find(ComparatorFunctionPointer(const CollectableType, comparator)) const
{
	for (find_index_t index = 0; index < this->Length(); index++)
		if (comparator(this->operator[](index))) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
	return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::FindLast(const CollectableType& value) const
{
	for (find_index_t index = this->Length() - 1; index >= 0; index--)
		if (this->operator[](index) == value) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
	return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::FindLast(const CollectableType&& value) const
{
	for (find_index_t index = this->Length() - 1; index >= 0; index--)
		if (this->operator[](index) == value) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
	return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::FindLast(ComparatorFunctionPointer(const CollectableType, comparator)) const
{
	for (find_index_t index = this->Length() - 1; index >= 0; index--)
		if (comparator(this->operator[](index))) return IndexValuePair<const CollectableType>(this->operator[](index), index, true);
	return IndexValuePair<const CollectableType>(nullref(CollectableType), -1, false);
}
#pragma endregion

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