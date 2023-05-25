#ifndef CollectionDefenitions_h
#define CollectionDefenitions_h

#include <stdint.h>

typedef uint32_t index_t;
typedef int64_t find_index_t;

#define nullref(T) (*(T*)nullptr)
#define is_nullref(expr) (&expr == nullptr)

#define safe_index(index, Length) (index % Length)
#define static_array_length(type, identifier) (sizeof(identifier) / sizeof(type))
#define static_array_fill(identifier, Length, value) for (index_t index_##identifier = 0; index_##identifier < Length; ++index_##identifier) identifier[index_##identifier] = value

#define ForEachIterator(type, name) void name(const index_t index, type& value)
#define ConstForEachIterator(type, name) void name(const index_t index, const type& value)
#define ForEachIteratorPointer(type, name) void(*name)(const index_t, type&)
#define ConstForEachIteratorPointer(type, name) void(*name)(const index_t, const type&)

#define ComparatorFunction(type, name) bool name(type& item)
#define ComparatorFunctionPointer(type, name) bool (*name)(type&)

#endif // !CollectionDefenitions_h