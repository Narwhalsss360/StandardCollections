#include <stdint.h>
#include <stddef.h>

typedef uint32_t index_t;
typedef int64_t find_index_t;

constexpr index_t index_t_max = UINT32_MAX;

const index_t ShrinkFindIndex(const find_index_t& findIndex)
{
	return findIndex % index_t_max;
}

const index_t ShrinkSize_t(const size_t& size)
{
	return size % index_t_max;
}