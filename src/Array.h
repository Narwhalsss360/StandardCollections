#ifndef Array_h
#define Array_h

#include "Collection.h"
#include <stdarg.h>
#ifdef initializer_list_supported
#include <initializer_list>
#endif // initializer_list_supported

#define Array_init(type, name, ...) type Array_init_##name[] __VA_ARGS__; auto name = CStyleToArray(Array_init_##name)

#pragma region Array
template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>::Array()
	: Collection<CollectableType>(), m_Array{ CollectableType() }
{
	FillCStyleArray(m_Array, CollectableType());
}

template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>::Array(CollectableType& fill)
	: Collection<CollectableType>(), m_Array{ CollectableType() }
{
	FillCStyleArray(m_Array, fill);
}

template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>::Array(CollectableType&& fill)
	: Collection<CollectableType>(), m_Array{ CollectableType() }
{
	FillCStyleArray(m_Array, fill);
}

template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>::Array(const Array& other)
	: Collection<CollectableType>(), m_Array{ CollectableType() }
{
	operator=(other);
}

template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>::Array(const Array&& other)
	: Collection<CollectableType>(), m_Array{ CollectableType() }
{
	operator=(other);
}

template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>::Array(CollectableType(&array)[TemplateLength])
	: Collection<CollectableType>(), m_Array{ CollectableType() }
{
	for (size_t index = 0; index < TemplateLength; index++)
		m_Array[index] = array[index];
}

#ifdef initializer_list_supported
template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>::Array(const std::initializer_list<CollectableType> initializer)
	: Collection<CollectableType>(), m_Array{ CollectableType() }
{
	operator=(initializer);
}
#endif // initializer_list_supported

template <typename CollectableType, index_t TemplateLength>
index_t Array<CollectableType, TemplateLength>::Length() const
{
	return TemplateLength;
}

template <typename CollectableType, index_t TemplateLength>
CollectableType& Array<CollectableType, TemplateLength>::operator[](index_t index)
{
	return m_Array[SafeIndex(index, TemplateLength)];
}

template <typename CollectableType, index_t TemplateLength>
const CollectableType& Array<CollectableType, TemplateLength>::operator[](index_t index) const
{
	return m_Array[SafeIndex(index, TemplateLength)];
}

template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>& Array<CollectableType, TemplateLength>::operator=(const Array<CollectableType, TemplateLength>& other)
{
	for (index_t index = 0; index < TemplateLength; index++)
		this->operator[](index) = other.operator[](index);
	return *this;
}

template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>::operator CollectableType* ()
{
	return m_Array;
}

#ifdef initializer_list_supported
template <typename CollectableType, index_t TemplateLength>
Array<CollectableType, TemplateLength>& Array<CollectableType, TemplateLength>::operator=(const std::initializer_list<CollectableType> initializer)
{
	for (size_t index = 0; index < (TemplateLength < initializer.size() ? TemplateLength : initializer.size()); index++)
		m_Array[index] = initializer.begin()[index];
	return *this;
}
#endif // initializer_list_supported
#pragma endregion

template <typename CStyleArrayType, index_t Length = sizeof(CStyleArrayType)>
inline Array<CStyleArrayType, Length> CStyleToArray(CStyleArrayType(&array)[Length])
{
	return Array<CStyleArrayType, Length>(array);
}

#endif // !Array_h