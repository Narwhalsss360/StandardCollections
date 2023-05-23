#ifndef Collection_h
#define Collection_h

#define safe_index(index, length) (index % length)
#define static_array_length(type, identifier) (sizeof(identifier) / sizeof(type))
#define static_array_fill(identifier, length, value) for (size_t index_##identifier = 0; index_##identifier < size; ++index_##identifier) identifier[index_##identifier] = value

template <typename CollectableTyoe>
class Collection
{
public:
	virtual inline size_t length() = 0;
	virtual inline CollectableTyoe& operator[](size_t) = 0;
	virtual inline const CollectableTyoe& operator[](size_t) const = 0;
};

#endif // !Collection_h