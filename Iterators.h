#ifndef Iterators_h
#define Iterators_h

#define nullref(T) *(T*)nullptr

template <typename CollectionType, typename DereferenceType>
class GeneralIterator
{
public:
	GeneralIterator(CollectionType& collection, const size_t index)
		: m_Collection(collection), m_CurrentIndex(index)
	{

	}

	virtual bool operator!=(GeneralIterator& other)
	{
		return m_CurrentIndex != other.m_CurrentIndex;
	}

	virtual void operator++()
	{
		m_CurrentIndex++;
	}

	virtual DereferenceType operator*()
	{
		return m_Collection[m_CurrentIndex];
	}

protected:
	CollectionType& m_Collection;
	size_t m_CurrentIndex;
};

struct DereferencedIteration
{
	DereferencedIteration(const bool defaulted = true)
		: defaulted(defaulted)
	{

	}

	const bool defaulted;
};

template <typename ValueType>
struct Enumeration : DereferencedIteration
{
	Enumeration(ValueType value)
		: DereferencedIteration(true), value(value), index(SIZE_MAX)
	{
	}

	Enumeration(ValueType value, size_t index)
		: DereferencedIteration(false), value(value), index(index)
	{
	}

	operator ValueType&()
	{
		return value;
	}

	ValueType value;
	const size_t index;
};

template <typename CollectionType, typename ValueType>
class EnumerationIterator : GeneralIterator<CollectionType, Enumeration<ValueType>>
{
public:
	EnumerationIterator(CollectionType& collection, const size_t index)
		: GeneralIterator<CollectionType, Enumeration<ValueType>>(collection, index)
	{
	}

	Enumeration<ValueType> operator*() override
	{
		return Enumeration<ValueType>(this->m_Collection[this->m_CurrentIndex], this->m_CurrentIndex);
	}
};

template <typename Zipped1ValueType, typename Zipped2ValueType>
struct Zipping : DereferencedIteration
{
	Zipping(Zipped1ValueType value1)
		: DereferencedIteration(true), value1(value1), value2(Zipped2ValueType()), index(SIZE_MAX)
	{
	}

	Zipping(Zipped1ValueType value1, Zipped2ValueType value2, const size_t index)
		: DereferencedIteration(false), value1(value1), value2(value2), index(index)
	{
	}

	operator Zipped1ValueType& ()
	{
		return value1;
	}

	operator Zipped2ValueType& ()
	{
		return value2;
	}

	Zipped1ValueType value1;
	Zipped2ValueType value2;
	const size_t index;
};

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType, typename Collection2Type = CollectionType>
class ZipIterator : GeneralIterator<CollectionType, Zipping<Zipped1ValueType, Zipped2ValueType>>
{
public:
	ZipIterator(CollectionType& collection, const size_t index)
		: GeneralIterator<CollectionType, Zipping<Zipped1ValueType, Zipped2ValueType>>(collection, index), m_Defaulted(true), m_Collection2(nullref(Collection2Type))
	{
	}

	ZipIterator(CollectionType& collection, Collection2Type& collection2, const size_t index)
		: GeneralIterator<CollectionType, Zipping<Zipped1ValueType, Zipped2ValueType>>(collection, index), m_Defaulted(false), m_Collection2(collection2)
	{
	}

	Zipping<Zipped1ValueType, Zipped2ValueType> operator*()
	{
		return Zipping<Zipped1ValueType, Zipped2ValueType>(this->m_Collection[this->m_CurrentIndex], m_Collection2[this->m_CurrentIndex], this->m_CurrentIndex);
	}

public:
	const bool m_Defaulted;

protected:
	Collection2Type& m_Collection2;
};

template <typename CollectionType, typename Iterator = GeneralIterator<CollectionType, CollectionType&>>
class GeneralIterable
{
public:
	GeneralIterable(CollectionType& collection, const size_t beginIndex, const size_t endIndex)
		: m_Collection(collection), m_BeginIndex(beginIndex), m_EndIndex(endIndex)
	{
	}

	virtual Iterator begin() const
	{
		return Iterator(m_Collection, m_BeginIndex);
	}

	virtual Iterator end() const
	{
		return Iterator(m_Collection, m_EndIndex);
	}

protected:
	CollectionType& m_Collection;
	const size_t m_BeginIndex, m_EndIndex;
};

template <typename CollectionType, typename Zipped1ValueType, typename Zipped2ValueType = Zipped1ValueType, typename Collection2Type = CollectionType>
class ZipIterable : GeneralIterable<CollectionType, ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>>
{
public:
	ZipIterable(CollectionType& collection, Collection2Type& collection2, const size_t beginIndex, const size_t endIndex)
		: GeneralIterable<CollectionType, ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>>(collection, beginIndex, endIndex), m_Collection2(collection2)
	{
	}

	ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> begin() const override
	{
		return ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>(this->m_Collection, m_Collection2, this->m_BeginIndex);
	}

	ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type> end() const override
	{
		return ZipIterator<CollectionType, Zipped1ValueType, Zipped2ValueType, Collection2Type>(this->m_Collection, m_Collection2, this->m_EndIndex);
	}

protected:
	Collection2Type& m_Collection2;
};

#endif // !Iterators_h