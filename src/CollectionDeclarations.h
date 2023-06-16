#ifndef CollectionDefenitions_h
#define CollectionDefenitions_h

#include <stdint.h>

#ifdef ARDUINO

#ifndef __collection_allocator__
#define __collection_allocator__(type, count) new type[count]
#endif

#ifndef __collection_freer__
#define __collection_freer__(identifier) delete[] identifier
#endif

#else
#define initializer_list_supported

#include <initializer_list>

#ifndef __collection_allocator__
#define __collection_allocator__(type, count) new type[count]
#endif

#ifndef __collection_freer__
#define __collection_freer__(identifier) delete[] identifier
#endif

#endif

typedef uint32_t index_t;
typedef int64_t find_index_t;

#define safe_index(index, Length) (Length == 0 ? 0 : (index % Length))
#define static_array_length(type, identifier) (sizeof(identifier) / sizeof(type))
#define static_array_fill(identifier, Length, value) for (index_t index_##identifier = 0; index_##identifier < Length; ++index_##identifier) identifier[index_##identifier] = value

#define ForEachIterator(type, name) void name(const index_t index, type& value)
#define ConstForEachIterator(type, name) void name(const index_t index, const type& value)
#define ForEachIteratorPointer(type, name) void(*name)(const index_t, type&)
#define ConstForEachIteratorPointer(type, name) void(*name)(const index_t, const type&)

#define PredicateFunction(type, name) bool name(type& item)
#define PredicateFunctionPointer(type, name) bool (*name)(type&)

#pragma region Forward Declarations
template <typename CollectionType, typename DereferenceType>
class GeneralIterator;

struct DereferencedIteration;

template <typename ValueType>
struct Enumeration;

template <typename CollectionType, typename ValueType>
class EnumerationIterator;

template <typename Zipped1ValueType, typename Zipped2ValueType>
struct Zipping;

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType = Zipped1ValueType, typename Collection2Type = CollectionType>
class ZipIterator;

template <typename CollectionType, typename Iterator = GeneralIterator<CollectionType, CollectionType&>>
class GeneralIterable;

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType = Zipped1ValueType, typename Collection2Type = CollectionType>
class ZipIterable;

template <typename ValueType>
struct IndexValuePair;

template <typename CollectableType>
class Collection;

template <typename CollectableType>
class DynamicCollection;

template <typename CollectableType, index_t TemplateLength = sizeof(CollectableType)>
class Array;

template <typename CollectableType>
class DynamicArray;
#pragma endregion

#pragma region Iterators
template <typename CollectionType, typename DereferenceType>
class GeneralIterator
{
public:
	GeneralIterator(CollectionType* const collection, const index_t index);

	virtual bool operator!=(GeneralIterator& other);

	virtual void operator++();

	virtual DereferenceType operator*();

	virtual index_t index();

protected:
	CollectionType* const m_Collection;
	index_t m_CurrentIndex;
};

struct DereferencedIteration
{
	DereferencedIteration(const bool defaulted = true);

	const bool defaulted;
};

template <typename ValueType>
struct Enumeration : public DereferencedIteration
{
	Enumeration(ValueType value);

	Enumeration(ValueType value, index_t index);

	operator ValueType& ();

	ValueType value;
	const index_t index;
};

template <typename CollectionType, typename ValueType>
class EnumerationIterator : public GeneralIterator<CollectionType, Enumeration<ValueType>>
{
public:
	EnumerationIterator(CollectionType* const collection, const index_t index);

	Enumeration<ValueType> operator*() override;
};

template <typename Zipped1ValueType, typename Zipped2ValueType>
struct Zipping : public DereferencedIteration
{
	Zipping(Zipped1ValueType value1);

	Zipping(Zipped1ValueType value1, Zipped2ValueType value2, const index_t index);

	Zipped1ValueType value1;
	Zipped2ValueType value2;
	const index_t index;
};

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
class ZipIterator : public GeneralIterator<CollectionType, Zipping<Zipped1ValueType, Zipped2ValueType>>
{
public:
	ZipIterator(CollectionType* const collection, const index_t index);

	ZipIterator(CollectionType* const collection, Collection2Type* const collection2, const index_t index);

	Zipping<Zipped1ValueType, Zipped2ValueType> operator*();

public:
	const bool m_Defaulted;

protected:
	Collection2Type* const m_Collection2;
};
#pragma endregion

#pragma region Iterables
template <typename CollectionType, typename Iterator>
class GeneralIterable
{
public:
	GeneralIterable(CollectionType* const collection, const index_t beginIndex, const index_t endIndex);

	virtual Iterator begin() const;

	virtual Iterator end() const;

protected:
	CollectionType* const m_Collection;
	const index_t m_BeginIndex, m_EndIndex;
};

template <typename Iterator>
class GeneralIteratorWrapper
{
public:
	GeneralIteratorWrapper(Iterator begin, Iterator end);

	Iterator begin() const;

	Iterator end() const;

protected:
	Iterator m_Begin;
	Iterator m_End;
};

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type>
class ZipIterable : public GeneralIterable<CollectionType, ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>>
{
public:
	ZipIterable(CollectionType* const collection, Collection2Type* const collection2, const index_t beginIndex, const index_t endIndex);

	ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> begin() const override;

	ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> end() const override;

protected:
	Collection2Type* const m_Collection2;
};
#pragma endregion

#pragma region Collections
template <typename ValueType>
struct IndexValuePair
{
	IndexValuePair();

	IndexValuePair(ValueType* value, find_index_t index, bool valid = false);

	operator ValueType& ();

	ValueType* value;
	const find_index_t index;
	const bool valid;
};

template <typename CollectableType>
class Collection
{
public:
	virtual inline index_t Length() const;

	virtual inline CollectableType& operator[](index_t) = 0;

	virtual inline const CollectableType& operator[](index_t) const = 0;

	virtual inline GeneralIterator<const Collection<CollectableType>, const CollectableType&> begin() const;

	virtual inline GeneralIterator<const Collection<CollectableType>, const CollectableType&> end() const;
#ifndef LightCollection_h
	virtual inline GeneralIterator<Collection<CollectableType>, CollectableType&> begin();

	virtual inline GeneralIterator<Collection<CollectableType>, CollectableType&> end();

	virtual inline void Fill(const CollectableType& value);

	virtual inline CollectableType& First();

	virtual inline const CollectableType& First() const;

	virtual inline CollectableType& Last();

	virtual inline const CollectableType& Last() const;

	virtual inline void ForEach(ForEachIteratorPointer(CollectableType, iterator));

	virtual inline void ForEach(ConstForEachIteratorPointer(CollectableType, iterator)) const;
#endif // LightCollection_h
	virtual inline IndexValuePair<const CollectableType> Find(const CollectableType& value) const;

	virtual inline IndexValuePair<const CollectableType> Find(PredicateFunctionPointer(const CollectableType, predicate)) const;

	virtual inline IndexValuePair<const CollectableType> FindLast(const CollectableType& value) const;

	virtual inline IndexValuePair<const CollectableType> FindLast(PredicateFunctionPointer(const CollectableType, predicate)) const;

	virtual inline index_t Count(const CollectableType& value) const;

	virtual inline index_t Count(PredicateFunctionPointer(const CollectableType, predicate)) const;

#ifndef LightCollection_h
	virtual inline DynamicArray<CollectableType> Slice(index_t startIndex, find_index_t endIndex = -1);

	virtual inline void CopyTo(Collection<CollectableType>& collection) const;

	virtual inline void MoveTo(Collection<CollectableType>& collection) const;
#endif // LightCollection_h

	virtual inline bool operator==(const Collection<CollectableType>& other) const;

	virtual inline bool operator!=(const Collection<CollectableType>& other) const;

	virtual inline bool operator<(const Collection<CollectableType>& other) const;

	virtual inline bool operator<=(const Collection<CollectableType>& other) const;

	virtual inline bool operator>(const Collection<CollectableType>& other) const;

	virtual inline bool operator>=(const Collection<CollectableType>& other) const;
};

template <typename CollectableType>
class DynamicCollection : public Collection<CollectableType>
{
public:
	virtual inline void Push(const CollectableType& item);

	virtual inline void Push(const Collection<CollectableType>& collection);

	virtual inline CollectableType Pop(bool shrink = false);

	virtual inline void Insert(index_t index, const CollectableType& item);

	virtual inline void Insert(index_t index, const Collection<CollectableType>& collection);

	virtual inline void Unshift(const CollectableType& item);

	virtual inline void Unshift(const Collection<CollectableType>& collection);

	virtual inline CollectableType Shift(bool shrink = false);

	virtual inline void Remove(index_t index, find_index_t count = -1, bool shrink = false);

	virtual inline void Join(const Collection<CollectableType>& collection);

	virtual inline index_t Capacity() const = 0;

	virtual inline DynamicCollection<CollectableType>& operator+=(const CollectableType& item);

	virtual inline DynamicCollection<CollectableType>& operator+=(const Collection<CollectableType>& item);

protected:
	virtual void SetLength(index_t newLength) = 0;

	virtual void SetCapacity(index_t newCapacity) = 0;
};

template <typename CollectableType, index_t TemplateLength>
class Array : public Collection<CollectableType>
{
public:
	Array();

	Array(const CollectableType& fill);

	Array(const Array& other);

	Array(const Array&& other);

	Array(CollectableType(&array)[TemplateLength]);

#ifdef initializer_list_supported
	Array(const std::initializer_list<CollectableType> initializer);
#endif // initializer_list_supported

	index_t Length() const override;

	CollectableType& operator[](index_t index) override;

	const CollectableType& operator[](index_t index) const override;

	Array<CollectableType, TemplateLength>& operator=(const Array<CollectableType, TemplateLength>& other);

	operator CollectableType* ();

#ifdef initializer_list_supported
	Array& operator=(const std::initializer_list<CollectableType> initializer);
#endif // initializer_list_supported

private:
	CollectableType m_Array[TemplateLength];
};

template <typename CollectableType>
class DynamicArray : public DynamicCollection<CollectableType>
{
public:

	inline DynamicArray();

	inline DynamicArray(DynamicArray<CollectableType>& other);

	inline DynamicArray(DynamicArray<CollectableType>&& other);

#ifdef initializer_list_supported
	inline DynamicArray(const std::initializer_list<CollectableType>& initializers);
#endif // initializer_list_supported

	inline index_t Capacity() const override;

	inline index_t Length() const override;

	CollectableType& operator[](const index_t index);

	const CollectableType& operator[](const index_t index) const;

	inline DynamicArray<CollectableType>& operator=(const DynamicArray<CollectableType>& other);

#ifdef initializer_list_supported
	DynamicArray<CollectableType>& operator=(const std::initializer_list<CollectableType>& initializers);
#endif // initializer_list_supported

	inline void SetLength(index_t newLength) override;

	inline void SetCapacity(index_t newCapacity) override;

	~DynamicArray();

private:

	CollectableType* m_Array;
	index_t m_Capacity;
	index_t m_Length;
};

#ifndef LightCollection_h
template <typename CollectableType, index_t JaggedCount, index_t JaggedLength>
using Jagged = Array<Array<CollectableType, JaggedLength>, JaggedCount>;

template <typename CollectableType, index_t JaggedLength>
using DynamicJagged = DynamicArray<Array<CollectableType, JaggedLength>>;

template <typename CollectableType, index_t JaggedCount>
using JaggedDynamic = Array<DynamicArray<CollectableType>, JaggedCount>;

template <typename CollectableType>
using DynamicJaggedDynamic = DynamicArray<DynamicArray<CollectableType>>;
#endif // LightCollection_h
#pragma endregion
#endif // !CollectionDefenitions_h