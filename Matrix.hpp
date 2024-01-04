/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:01:45 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/04 01:22:16 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP
# include <iostream>
# include <vector>
# include <initializer_list>
# include <stdexcept>
# include <cmath>

# define MAT_REGULAR 0
# define MAT_VECTOR 1
# define MAT_IDENTITY 2
typedef uint8_t Mat_type;

template <typename T>
class Matrix
{
private	:
	const size_t	_rows;
	const size_t	_columns;
	std::vector<T>	_data;

	size_t	index(const uint8_t i, const uint8_t j) const noexcept
	{ return (i * this->_columns + j); };
	bool	isSameSize(const Matrix &obj) const noexcept
	{ return (obj.getCols() == this->getCols() && obj.getRows() == this->getRows()); };
	bool	canMultiply(const Matrix &obj) const noexcept
	{ return (obj.getRows() == this->getCols()); };

public	:
	Matrix(const size_t rows, const size_t columns, Mat_type type = MAT_REGULAR);
	Matrix(const Matrix &obj);
	Matrix(const size_t rows, const size_t columns,
		std::initializer_list<T> data);
	~Matrix() {};

	size_t	getRows() const noexcept { return this->_rows; };
	size_t	getCols() const noexcept { return this->_columns; };
	const T	*getData() const noexcept { return this->_data.data(); };

	T		getElem(const uint8_t i, const uint8_t j) const;
	void	setElem(const uint8_t i, const uint8_t j, const T n);

	Matrix	&operator=(const Matrix &obj);
	Matrix	operator+(const Matrix &obj) const;
	Matrix	operator-(const Matrix &obj) const;
	Matrix	operator*(const T n) const;
	Matrix	operator*(const Matrix &obj) const;
	Matrix	operator/(const T n) const;

	static bool	isVector(const Matrix &obj) noexcept
	{ return (obj.getRows() == 1 || obj.getCols() == 1); };
	static bool	isSameSize(const Matrix &obj1, const Matrix &obj2) noexcept
	{ return (obj1.getCols() == obj2.getCols() && obj1.getRows() == obj2.getRows()); };
	static bool	canMultiply(const Matrix &obj1, const Matrix &obj2) noexcept
	{ return (obj1.getRows() == obj2.getCols()); };

	static T	vec2DLength(const Matrix &obj);
	static T	vec3DLength(const Matrix &obj);

	static Matrix	transpose(const Matrix &obj);
	static Matrix	average(const Matrix &obj1, const Matrix &obj2);

	static Matrix	scaling(const T x, const T y);
	static Matrix	scaling(const T x, const T y, const T z);
	static Matrix	translation(const T x, const T y);
	static Matrix	translation(const T x, const T y, const T z);
};

template <typename T>
Matrix<T>		operator*(const T n, const Matrix<T> &obj);
template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Matrix<T> &obj);

# include "Matrix.tpp"

#endif