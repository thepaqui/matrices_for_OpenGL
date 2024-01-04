/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:01:45 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/04 17:45:29 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP
# include <iostream>
# include <vector>
# include <initializer_list>
# include <stdexcept>

# include <cmath>
# ifndef  M_PI
#  define  M_PI  3.1415926535897932384626433
# endif

typedef enum
{
	Mat_null,
	Mat_vector,
	Mat_identity
}	Mat_type;

typedef enum
{
	Vec_axis,
	Vec_point
}	Vec_type;

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
	Matrix(const size_t rows, const size_t columns, const Mat_type type = Mat_null);
	Matrix(const Matrix &obj);
	Matrix(const size_t rows, const size_t columns, const std::initializer_list<T> data);
	Matrix(const T x, const T y, const T z, const Vec_type type);
	~Matrix() {};

	size_t	getRows() const noexcept { return this->_rows; };
	size_t	getCols() const noexcept { return this->_columns; };
	size_t	getSize() const noexcept { return (this->_rows * this->_columns); };
	const T	*getData() const noexcept { return this->_data.data(); };

	T		getElem(const size_t i, const size_t j) const;
	T		getElem(const size_t ind) const;
	void	setElem(const size_t i, const size_t j, const T n);
	void	setElem(const size_t ind, const T n);

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

	static T	degToRad(const T deg) noexcept
	{ return (deg * (M_PI / 180)); };
	static T	radToDeg(const T rad) noexcept
	{ return (rad * (180 / M_PI)); };

	static T	vec2DLength(const Matrix &obj);
	static T	vec3DLength(const Matrix &obj);
	static T	vecLength(const Matrix &obj);

	static Matrix	normalize(const Matrix &obj);
	static Matrix	transpose(const Matrix &obj);
	static Matrix	average(const Matrix &obj1, const Matrix &obj2);

	// Transformations

	static Matrix	scaling2D(const T x, const T y);
	static Matrix	scaling3D(const T x, const T y, const T z);

	static Matrix	rotation2D(const T angleInDegrees);
	static Matrix	rotationX3D(const T angleInDegrees);
	static Matrix	rotationY3D(const T angleInDegrees);
	static Matrix	rotationZ3D(const T angleInDegrees);
	static Matrix	rotation3D(const T angleInDegrees, const Matrix &axis);
	static Matrix	axis(const T x, const T y, const T z);

	static Matrix	translation2D(const T x, const T y);
	static Matrix	translation3D(const T x, const T y, const T z);
};

template <typename T>
Matrix<T>		operator*(const T n, const Matrix<T> &obj);
template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Matrix<T> &obj);

# include "Matrix.tpp"

#endif