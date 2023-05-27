#ifndef DynamicCollection_h
#define DynamicCollection_h

#include "CollectionDeclarations.h"

template <typename CollectableType>
void DynamicCollection<CollectableType>::Push(CollectableType&& item)
{
	Insert((this->Length() ? this->Length(): 0), item);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Push(CollectableType& item)
{
	Insert((this->Length() ? this->Length() : 0), item);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Push(Collection<CollectableType>&& collection)
{
	Insert((this->Length() ? this->Length() : 0), collection);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Push(Collection<CollectableType>& collection)
{
	Insert((this->Length() ? this->Length(): 0), collection);
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
void DynamicCollection<CollectableType>::Insert(index_t index, CollectableType&& item)
{
	if (this->Length() >= this->Capacity())
		SetCapacity(this->Length() + 1);

	SetLength(this->Length() + 1);
	for (find_index_t iIndex = this->Length() - 1; iIndex > index; iIndex--)
		this->operator[](iIndex) = this->operator[](iIndex - 1);

	this->operator[](index) = item;
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Insert(index_t index, CollectableType& item)
{
	if (this->Length() >= this->Capacity())
		SetCapacity(this->Length() + 1);

	SetLength(this->Length() + 1);
	for (find_index_t iIndex = this->Length() - 1; iIndex > index; iIndex--)
		this->operator[](iIndex) = this->operator[](iIndex - 1);

	this->operator[](index) = item;
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Insert(index_t index, Collection<CollectableType>&& collection)
{
	if (this->Length() + collection.Length() >= this->Capacity())
		SetCapacity(this->Length() + collection.Length());

	SetLength(this->Length() + collection.Length());
	for (find_index_t iIndex = this->Length() - 1; iIndex > index; iIndex--)
		this->operator[](iIndex) = this->operator[](iIndex - 1 - collection.Length()); //Test

	for (index_t iIndex = 0; iIndex < collection.Length(); iIndex++)
		this->operator[](iIndex + index) = collection[iIndex];
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Insert(index_t index, Collection<CollectableType>& collection)
{
	if (this->Length() + collection.Length() >= this->Capacity())
		SetCapacity(this->Length() + collection.Length());

	SetLength(this->Length() + collection.Length());
	for (find_index_t iIndex = this->Length() - 1; iIndex = index; iIndex--)
		this->operator[](iIndex) = this->operator[](iIndex - 1 - collection.Length()); //Test

	for (find_index_t iIndex = 0; iIndex < collection.Length(); iIndex++)
		this->operator[](iIndex + index) = collection[iIndex];
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Unshift(CollectableType&& item)
{
	Insert(0, item);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Unshift(CollectableType& item)
{
	Insert(0, item);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Unshift(Collection<CollectableType>&& collection)
{
	Insert(0, collection);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Unshift(Collection<CollectableType>& collection)
{
	Insert(0, collection);
}

template <typename CollectableType>
CollectableType DynamicCollection<CollectableType>::Shift(bool shrink)
{
	CollectableType returnValue = this->operator[](0);
	for (index_t index = this->Length() - 1; index > 0; index++)
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
		SetCapacity(this->Length() - index);
		return;
	}

	SetLength(this->Length() - count);
}

template <typename CollectableType>
void DynamicCollection<CollectableType>::Join(Collection<CollectableType>& collection)
{
	Insert(this->Length() - 1, collection);
}

#endif // !DynamicCollection_h