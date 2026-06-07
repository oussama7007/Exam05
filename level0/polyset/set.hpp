#pragma once

#include "searchable_bag.hpp"

class set
{
private:
	searchable_bag *_bag;

public:
	set();
	set(searchable_bag &bag);
	set(const set &other);
	set &operator=(const set &other);
	~set();

	bool has(int value) const;
	void insert(int value);
	void insert(int *array, int size);
	void print() const;
	void clear();

	const searchable_bag &get_bag() const;
};