#include "vect2.hpp"

int vect2::idx(int index)
{
	return (index == 0 ? 0 : 1);
}

vect2 &vect2::add(int x, int y)
{
	_v[0] += x;
	_v[1] += y;
	return *this;
}

vect2 &vect2::mult(int n)
{
	_v[0] *= n;
	_v[1] *= n;
	return *this;
}

vect2::vect2(int x, int y)
{
	_v[0] = x;
	_v[1] = y;
}

vect2::vect2(const vect2 &other)
{
	*this = other;
} 

vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		_v[0] = other._v[0];
		_v[1] = other._v[1];
	}
	return *this;
}

int vect2::operator[](int index) const
{
	return _v[idx(index)];
}

int &vect2::operator[](int index)
{
	return _v[idx(index)];
}

vect2 &vect2::operator++()
{
	return add(1, 1);
}

vect2 vect2::operator++(int)
{
	vect2 tmp(*this);
	++(*this);
	return tmp;
}

vect2 &vect2::operator--()
{
	return add(-1, -1);
}

vect2 vect2::operator--(int)
{
	vect2 tmp(*this);
	--(*this);
	return tmp;
}

vect2 &vect2::operator+=(const vect2 &other)
{
	return add(other[0], other[1]);
}

vect2 vect2::operator+(const vect2 &other) const
{
	vect2 tmp(*this);
	tmp += other;
	return tmp;
}

vect2 &vect2::operator-=(const vect2 &other)
{
	return add(-other[0], -other[1]);
}

vect2 vect2::operator-(const vect2 &other) const
{
	vect2 tmp(*this);
	tmp -= other;
	return tmp;
}

vect2 &vect2::operator*=(int scalar)
{
	return mult(scalar);
}

vect2 vect2::operator*(int scalar) const
{
	vect2 tmp(*this);
	tmp *= scalar;
	return tmp;
}

vect2 vect2::operator+() const
{
	return *this;
}

vect2 vect2::operator-() const
{
	return vect2(-_v[0], -_v[1]);
}

bool vect2::operator==(const vect2 &other) const
{
	return (_v[0] == other._v[0] && _v[1] == other._v[1]);
}

bool vect2::operator!=(const vect2 &other) const
{
	return !(*this == other);
}

vect2 operator*(int scalar, const vect2 &v)
{
	return v * scalar;
}

std::ostream &operator<<(std::ostream &out, const vect2 &v)
{
	out << "{" << v[0] << ", " << v[1] << "}";
	return out;
}