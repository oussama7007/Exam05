#include "set.hpp"

set::set() : _bag(0) {}

set::set(searchable_bag &bag) : _bag(&bag) {}

set::set(const set &other) : _bag(other._bag) {}

set &set::operator=(const set &other)
{
	if (this != &other)
		_bag = other._bag;
	return *this;
}

set::~set() {}

bool set::has(int value) const
{
	if (!_bag)
		return false;
	return _bag->has(value);
}

void set::insert(int value)
{
	if (_bag && !_bag->has(value))
		_bag->insert(value);
}

void set::insert(int *array, int size)
{
	if (!_bag || !array)
		return;

	int i = 0;
	while (i < size)
	{
		insert(array[i]);
		i++;
	}
}

void set::print() const
{
	if (_bag)
		_bag->print();
}

void set::clear()
{
	if (_bag)
		_bag->clear();
}

const searchable_bag &set::get_bag() const
{
	return *_bag;
}