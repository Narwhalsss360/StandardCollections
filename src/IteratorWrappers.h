#ifndef IteratorWrapper_h
#define IteratorWrapper_h

#include "Iterators.h"
#include "Collection.h"

#pragma region Iterate
template <typename CStyleArrayType, index_t Length = sizeof(CStyleArrayType)>
inline GeneralIterable<CStyleArrayType[Length], GeneralIterator<CStyleArrayType[Length], CStyleArrayType&>> Iterate(CStyleArrayType(&array)[Length])
{
	return GeneralIterable<CStyleArrayType[Length], GeneralIterator<CStyleArrayType[Length], CStyleArrayType&>>(&array, 0, Length);
}

template <typename CollectableType>
GeneralIterable<Collection<CollectableType>, GeneralIterator<Collection<CollectableType>, CollectableType&>> Iterate(Collection<CollectableType>& collection)
{
	return GeneralIterable<Collection<CollectableType>, GeneralIterator<Collection<CollectableType>, CollectableType&>>(&collection, 0, collection.Length());
}

template <typename CollectableType>
GeneralIterable<const Collection<CollectableType>, GeneralIterator<const Collection<CollectableType>, const CollectableType&>> Iterate(const Collection<CollectableType>& collection)
{
	return GeneralIterable<const Collection<CollectableType>, GeneralIterator<const Collection<CollectableType>, const CollectableType&>>(&collection, 0, collection.Length());
}

template <typename CollectionType, typename DereferenceType>
GeneralIteratorWrapper<GeneralIterator<CollectionType, DereferenceType>> Iterate(GeneralIterator<CollectionType, DereferenceType> begin, GeneralIterator<CollectionType, DereferenceType> end)
{
	return GeneralIteratorWrapper<GeneralIterator<CollectionType, DereferenceType>>(begin, end);
}
#pragma endregion

#pragma region Enumerate
template <typename CStyleArrayType, index_t Length = sizeof(CStyleArrayType)>
inline GeneralIterable<CStyleArrayType[Length], EnumerationIterator<CStyleArrayType[Length], CStyleArrayType&>> Enumerate(CStyleArrayType(&array)[Length])
{
	return GeneralIterable<CStyleArrayType[Length], EnumerationIterator<CStyleArrayType[Length], CStyleArrayType&>>(&array, 0, Length);
}

template <typename CollectableType>
GeneralIterable<Collection<CollectableType>, EnumerationIterator<Collection<CollectableType>, CollectableType&>> Enumerate(Collection<CollectableType>& collection)
{
	return GeneralIterable<Collection<CollectableType>, EnumerationIterator<Collection<CollectableType>, CollectableType&>>(&collection, 0, collection.Length());
}

template <typename CollectableType>
GeneralIterable<const Collection<CollectableType>, EnumerationIterator<const Collection<CollectableType>, const CollectableType&>> Enumerate(const Collection<CollectableType>& collection)
{
	return GeneralIterable<const Collection<CollectableType>, EnumerationIterator<const Collection<CollectableType>, const CollectableType&>>(&collection, 0, collection.Length());
}

template <typename CollectionType, typename DereferenceType>
GeneralIteratorWrapper<EnumerationIterator<CollectionType, DereferenceType>> Enumerate(EnumerationIterator<CollectionType, DereferenceType> begin, EnumerationIterator<CollectionType, DereferenceType> end)
{
	return GeneralIteratorWrapper<EnumerationIterator<CollectionType, DereferenceType>>(begin, end);
}
#pragma endregion

#pragma region Zip
template <typename CStyleArrayType1, typename CStyleArrayType2 = CStyleArrayType1, index_t Array1Length = sizeof(CStyleArrayType1), index_t Array2Length = sizeof(CStyleArrayType2)>
inline ZipIterable<CStyleArrayType1[Array1Length], CStyleArrayType1&, CStyleArrayType2&, CStyleArrayType2[Array2Length]> Zip(CStyleArrayType1(&array1)[Array1Length], CStyleArrayType2(&array2)[Array2Length])
{
	return ZipIterable<CStyleArrayType1[Array1Length], CStyleArrayType1&, CStyleArrayType2&, CStyleArrayType2[Array2Length]>(&array1, &array2, 0, (Array1Length < Array2Length) ? Array1Length : Array2Length);
}

template <typename CollectableType, typename CollectableType2>
ZipIterable<Collection<CollectableType>, CollectableType&, CollectableType2&, Collection<CollectableType2>> Zip(Collection<CollectableType>& collection1, Collection<CollectableType2>& collection2)
{
	return ZipIterable<Collection<CollectableType>, CollectableType&, CollectableType2&, Collection<CollectableType2>>(&collection1, &collection2, 0, (collection1.Length() < collection2.Length()) ? collection1.Length() : collection2.Length());
}

template <typename CollectableType, typename CollectableType2>
ZipIterable<const Collection<CollectableType>, const CollectableType&, const CollectableType2&, const Collection<CollectableType2>> Zip(const Collection<CollectableType>& collection1, const Collection<CollectableType2>& collection2)
{
	return ZipIterable<const Collection<CollectableType>, const CollectableType&, const CollectableType2&, const Collection<CollectableType2>>(&collection1, &collection2, 0, (collection1.Length() < collection2.Length()) ? collection1.Length() : collection2.Length());
}

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
GeneralIteratorWrapper<ZipIterator<CollectionType, Zipped1ValueType&, Zipped2ValueType&, Collection2Type>> Zip(ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> begin, ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> end)
{
	return GeneralIteratorWrapper<ZipIterator<CollectionType, Zipped1ValueType&, Zipped2ValueType&, Collection2Type>>(begin, end);
}

template <typename CollectableType, typename CollectableType2>
ZipIterable<const Collection<CollectableType>, const CollectableType, const CollectableType2, const Collection<CollectableType2>> ZipCopy(const Collection<CollectableType>& collection1, const Collection<CollectableType2>& collection2)
{
	return ZipIterable<const Collection<CollectableType>, const CollectableType, const CollectableType2, const Collection<CollectableType2>>(&collection1, &collection2, 0, (collection1.Length() < collection2.Length()) ? collection1.Length() : collection2.Length());
}

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
GeneralIteratorWrapper<ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>> ZipCopy(ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> begin, ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> end)
{
	return GeneralIteratorWrapper<ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>>(begin, end);
}
#pragma endregion
#endif // !IteratorWrapper_h