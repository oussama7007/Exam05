#pragma once

#include <iostream>

class vect2
{
	private:
		int _v[2];

		static int idx(int index);
		vect2 &add(int x, int y);
		vect2 &mult(int n);

	public:
		vect2(int x = 0, int y = 0);
		vect2(const vect2 &other);

		vect2 &operator=(const vect2 &other);

		int operator[](int index) const;
		int &operator[](int index);

		vect2 &operator++();
		vect2 operator++(int);

		vect2 &operator--();
		vect2 operator--(int);

		vect2 &operator+=(const vect2 &other);
		vect2 operator+(const vect2 &other) const;

		vect2 &operator-=(const vect2 &other);
		vect2 operator-(const vect2 &other) const;

		vect2 &operator*=(int scalar);
		vect2 operator*(int scalar) const;

		vect2 operator+() const;
		vect2 operator-() const;

		bool operator==(const vect2 &other) const;
		bool operator!=(const vect2 &other) const;
};

vect2 operator*(int scalar, const vect2 &v);
std::ostream &operator<<(std::ostream &out, const vect2 &v);