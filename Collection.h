#pragma once

template <typename CollectableTyoe>
class Collection
{
public:
	virtual inline size_t length() = nullptr;
	virtual inline CollectableTyoe& operator[](size_t) = nullptr;
	virtual inline const CollectableTyoe& oprator[](size_t) const = nullptr;

};