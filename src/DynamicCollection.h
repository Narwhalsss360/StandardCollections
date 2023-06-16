#ifndef DynamicCollection_h
#define DynamicCollection_h

#include "CollectionDeclarations.h"

template <typename CollectableType>
void DynamicCollection<CollectableType>::Push(const CollectableType& item)
{
	Insert(this->Length(), item);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Push(const Collection<CollectableType>& collection)
{
	Insert(this->Length(), collection);
}

template <typename CollectableType>
CollectableType DynamicCollection<CollectableType>::Pop(bool shrink)
{
	CollectableType returnValue = this->operator[](this->Length() - 1);

	SetLength(this->Length() - 1);

	if (shrink)
		SetCapacity(this->Length());

	return returnValue;
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Insert(index_t index, const CollectableType& item)
{
	if (this->Length() >= this->Capacity())
		SetCapacity(this->Length() + 1);

	SetLength(this->Length() + 1);
	for (find_index_t iIndex = this->Length() - 1; iIndex > index; iIndex--)
		this->operator[](iIndex) = this->operator[](iIndex - 1);

	this->operator[](index) = item;
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Insert(index_t index, const Collection<CollectableType>& collection)
{
	if (Capacity() < this->Length() + collection.Length())
		SetCapacity(this->Length() + collection.Length());

	for (index_t collectionIndex = 0; collectionIndex < collection.Length(); collectionIndex++)
		this->Insert(index + collectionIndex, collection[collectionIndex]);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Unshift(const CollectableType& item)
{
	Insert(0, item);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Unshift(const Collection<CollectableType>& collection)
{
	Insert(0, collection);
}

template <typename CollectableType>
CollectableType DynamicCollection<CollectableType>::Shift(bool shrink)
{
	CollectableType returnValue = this->operator[](0);

	for (find_index_t index = this->Length() - 1; index > 0; index++)
		this->operator[](index) = this->operator[](index - 1);

	SetLength(this->Length() - 1);

	if (shrink)
		SetCapacity(this->Length());

	return returnValue;
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Remove(index_t index, find_index_t count, bool shrink)
{
	if (count == -1)
	{
		SetCapacity(index + 1);
		return;
	}

	for (index_t keepIndex = index + count; keepIndex < this->Length(); keepIndex++)
		this->operator[](keepIndex - count) = this->operator[](keepIndex);

	SetCapacity(this->Length() - count);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Join(const Collection<CollectableType>& collection)
{
	Insert(this->Length(), collection);
}

template <typename CollectableType>
DynamicCollection<CollectableType>& DynamicCollection<CollectableType>::operator+=(const CollectableType& item)
{
	Push(item);
	return *this;
}

template <typename CollectableType>
DynamicCollection<CollectableType>& DynamicCollection<CollectableType>::operator+=(const Collection<CollectableType>& item)
{
	Push(item);
	return *this;
}
#endif // !DynamicCollection_h