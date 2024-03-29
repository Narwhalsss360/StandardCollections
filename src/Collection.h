#ifndef Collection_h
#define Collection_h

#include "CollectionDeclarations.h"
#include "Iterators.h"

#pragma region IndexValuePair
template <typename ValueType>
IndexValuePair<ValueType>::IndexValuePair()
	: value(nullptr), index(SIZE_MAX), valid(false)
{
}

template <typename ValueType>
IndexValuePair<ValueType>::IndexValuePair(ValueType* value, find_index_t index, bool valid)
	: value(value), index(index), valid(value != nullptr)
{
}

template <typename ValueType>
IndexValuePair<ValueType>::operator ValueType&()
{
	return *value;
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
	return GeneralIterator<const Collection<CollectableType>, const CollectableType&>(this, 0);
}

template <typename CollectableType>
GeneralIterator<const Collection<CollectableType>, const CollectableType&> Collection<CollectableType>::end() const
{
	return GeneralIterator<const Collection<CollectableType>, const CollectableType&>(this, Length());
}

#ifndef LightCollection_h
template <typename CollectableType>
GeneralIterator<Collection<CollectableType>, CollectableType&> Collection<CollectableType>::begin()
{
	return GeneralIterator<Collection<CollectableType>, CollectableType&>(this, 0);
}

template <typename CollectableType>
GeneralIterator<Collection<CollectableType>, CollectableType&> Collection<CollectableType>::end()
{
	return GeneralIterator<Collection<CollectableType>, CollectableType&>(this, Length());
}

template <typename CollectableType>
void Collection<CollectableType>::Fill(const CollectableType& value)
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
void Collection<CollectableType>::ForEach(ConstForEachIteratorPointer(CollectableType, iterator)) const
{
	for (index_t index = 0; index < Length(); ++index)
		iterator(index, this->operator[](index));
}
#endif // !LightCollection_h

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::Find(const CollectableType& value) const
{
	for (find_index_t index = 0; index < this->Length(); index++)
		if (this->operator[](ShrinkFindIndex(index)) == value)
			return IndexValuePair<const CollectableType>(&(this->operator[](ShrinkFindIndex(index))), index, true);
	return IndexValuePair<const CollectableType>(nullptr, -1, false);
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::Find(PredicateFunctionPointer(const CollectableType, predicate)) const
{
	for (find_index_t index = 0; index < this->Length(); index++)
		if (predicate(this->operator[](ShrinkFindIndex(index))))
			return IndexValuePair<const CollectableType>(&(this->operator[](ShrinkFindIndex(index))), index, true);
	return IndexValuePair<const CollectableType>(nullptr, -1, false);
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::FindLast(const CollectableType& value) const
{
	for (find_index_t index = this->Length() - 1; index >= 0; index--)
		if (this->operator[](ShrinkFindIndex(index)) == value)
			return IndexValuePair<const CollectableType>(&(this->operator[](ShrinkFindIndex(index))), index, true);
	return IndexValuePair<const CollectableType>(nullptr, -1, false);
}

template <typename CollectableType>
IndexValuePair<const CollectableType> Collection<CollectableType>::FindLast(PredicateFunctionPointer(const CollectableType, predicate)) const
{
	for (find_index_t index = this->Length() - 1; index >= 0; index--)
		if (predicate(this->operator[](ShrinkFindIndex(index))))
			return IndexValuePair<const CollectableType>(&(this->operator[](ShrinkFindIndex(index))), index, true);
	return IndexValuePair<const CollectableType>(nullptr, -1, false);
}

template <typename CollectableType>
index_t Collection<CollectableType>::Count(const CollectableType& value) const
{
	index_t count = 0;
	for (index_t index = 0; index < this->Length(); index++)
		if (this->operator[](index) == value)
			count++;
	return count;
}

template <typename CollectableType>
index_t Collection<CollectableType>::Count(PredicateFunctionPointer(const CollectableType, predicate)) const
{
	index_t count = 0;
	for (index_t index = 0; index < this->Length(); index++)
		if (predicate(this->operator[](index)))
			count++;
	return count;
}

#ifndef LightCollection_h
template <typename CollectableType>
DynamicArray<CollectableType> Collection<CollectableType>::Slice(index_t startIndex, find_index_t endIndex)
{
	endIndex = endIndex == -1 ? this->Length() - 1: endIndex;

	DynamicArray<CollectableType> returnCollection;

	for (index_t index = startIndex; index <= endIndex; index++)
		returnCollection.Push(this->operator[](index));

	return returnCollection;
}

template <typename CollectableType>
void Collection<CollectableType>::CopyTo(Collection<CollectableType>& collection) const
{
	for (index_t index = 0; index < (this->Length() < collection.Length() ? this->Length() : collection.Length()); index++)
		collection.operator[](index) = this->operator[](index);
}

template <typename CollectableType>
void Collection<CollectableType>::MoveTo(Collection<CollectableType>& collection) const
{
	CopyTo(collection);
}
#endif // !LightCollection_h

template <typename CollectableType>
bool Collection<CollectableType>::operator==(const Collection<CollectableType>& other) const
{
	if (this->Length() != other.Length())
		return false;
	for (index_t index = 0; index < this->Length(); index++)
		if (!(this->operator[](index) == other.operator[](index)))
			return false;
	return true;
}

template <typename CollectableType>
bool Collection<CollectableType>::operator!=(const Collection<CollectableType>& other) const
{
	return !this->operator==(other);
}

template <typename CollectableType>
bool Collection<CollectableType>::operator<(const Collection<CollectableType>& other) const
{
	return this->Length() < other.Length();
}

template <typename CollectableType>
bool Collection<CollectableType>::operator<=(const Collection<CollectableType>& other) const
{
	return this->Length() <= other.Length();
}

template <typename CollectableType>
bool Collection<CollectableType>::operator>(const Collection<CollectableType>& other) const
{
	return this->Length() > other.Length();
}

template <typename CollectableType>
bool Collection<CollectableType>::operator>=(const Collection<CollectableType>& other) const
{
	return this->Length() >= other.Length();
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
inline constexpr index_t CollectionLength(CStyleArrayType(&array)[Length])
{
	return Length;
}

template <typename CollectableType>
inline const index_t CollectionLength(Collection<CollectableType>& collection)
{
	return collection.Length();
}

template <typename SourceType, typename DestinationType, typename SourceCollectionType, typename DestinationCollectionType>
inline void CastCollection(SourceCollectionType& source, DestinationCollectionType& destination)
{
	for (index_t index = 0; index < CollectionLength(source); index++)
		destination[index] = (DestinationType)source[index];
}

template <typename SourceType, typename DestinationType, typename SourceCollectionType, typename DestinationCollectionType>
inline void CastCollection(SourceCollectionType& source, DestinationCollectionType& destination, DestinationType (*caster)(SourceType&))
{
	for (index_t index = 0; index < CollectionLength(source); index++)
		destination[index] = caster(source[index]);
}
#endif // !Collection_h