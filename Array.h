#ifndef Array_h
#define Array_h

#include "Collection.h"
#include "Iterators.h"
#include <stdarg.h>
#ifdef __cpp_initializer_lists
#include <initializer_list>
#endif // __cpp_initializer_lists

#define Array_init(type, name, ...) type Array_init_##name[] __VA_ARGS__; auto name = CStyleToArray(Array_init_##name)

template <typename CollectableType, size_t Length = sizeof(CollectableType)>
class Array : public Collection<CollectableType>
{
public:
	Array()
		: Collection<CollectableType>(), m_Array{ CollectableType() }
	{
		FillCStyleArray(m_Array, CollectableType());
	}

	Array(CollectableType& fill)
		: Collection<CollectableType>(), m_Array{ CollectableType() }
	{
		FillCStyleArray(m_Array, fill);
	}

	Array(CollectableType&& fill)
		: Collection<CollectableType>(), m_Array{ CollectableType() }
	{
		FillCStyleArray(m_Array, fill);
	}

	Array(const Array& other)
		: Collection<CollectableType>(), m_Array{ CollectableType() }
	{
		operator=(other);
	}

	Array(const Array&& other)
		: Collection<CollectableType>(), m_Array{ CollectableType() }
	{
		operator=(other);
	}

	Array(CollectableType(&array)[Length])
		: Collection<CollectableType>(), m_Array{ CollectableType() }
	{
		for (size_t index = 0; index < Length; index++)
			m_Array[index] = array[index];
	}

#if __cpp_initializer_lists
		Array(const std::initializer_list<CollectableType> initializer)
		: Collection<CollectableType>(), m_Array{ CollectableType() }
	{
		operator=(initializer);
	}
#endif // __cpp_initializer_lists

	size_t length() const override
	{
		return Length;
	}

	CollectableType& operator[](size_t index) override
	{
		return m_Array[SafeIndex(index, Length)];
	}

	const CollectableType& operator[](size_t index) const override
	{
		return m_Array[SafeIndex(index, Length)];
	}

	operator CollectableType* ()
	{
		return m_Array;
	}

	Array& operator=(const Array& other)
	{
		for (size_t index = 0; index < Length; index++)
			m_Array[index] = other[index];
		return *this;
	}

	Array& operator=(const Array&& other)
	{
		return *this;
	}

#ifdef __cpp_initializer_lists
	Array& operator=(const std::initializer_list<CollectableType> initializer)
	{
		for (size_t index = 0; index < (Length < initializer.size() ? Length : initializer.size()); index++)
			m_Array[index] = initializer.begin()[index];
		return *this;
	}
#endif // __cpp_initializer_lists

private:
	CollectableType m_Array[Length];
};

template <typename CStyleArrayType, size_t Length = sizeof(CStyleArrayType)>
inline Array<CStyleArrayType, Length> CStyleToArray(CStyleArrayType(&array)[Length])
{
	return Array<CStyleArrayType, Length>(array);
}

#endif // !Array_h