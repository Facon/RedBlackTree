#pragma once

#include <cstdint>

class Set
{
public:
	Set() = default;
	virtual ~Set() = default;

	virtual size_t size() const = 0;
	virtual bool isEmpty() const;
	virtual void insert(int key) = 0;
	virtual bool contains(int key) const = 0;
	virtual void remove(int key) = 0;
};
