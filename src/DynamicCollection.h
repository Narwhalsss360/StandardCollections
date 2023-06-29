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
	this->Remove(this->Length() - 1, 1, shrink);
	return returnValue;
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Insert(index_t index, const CollectableType& item)
{
	if (this->Length() >= this->Capacity())
		SetCapacity(this->Length() + 1);

	SetLength(this->Length() + 1);
	for (find_index_t iIndex = this->Length() - 1; iIndex > index; iIndex--)
		this->operator[](ShrinkFindIndex(iIndex)) = this->operator[](ShrinkFindIndex(iIndex - 1));

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
	this->Remove(0, 1, shrink);
	return returnValue;
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Remove(index_t index, find_index_t count, bool shrink)
{
	if (index + count > this->Length())
		count = -1;

	if (count == -1)
	{
		SetCapacity(index + 1);
		return;
	}

	for (index_t keepIndex = index + ShrinkFindIndex(count); keepIndex < this->Length(); keepIndex++)
		this->operator[](keepIndex - ShrinkFindIndex(count)) = this->operator[](keepIndex);

	SetLength(this->Length() - ShrinkFindIndex(count));
	if (shrink)
		SetCapacity(this->Length() - ShrinkFindIndex(count));
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