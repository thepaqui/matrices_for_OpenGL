/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:01:45 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/10 14:14:48 by thepaqui         ###   ########.fr       */
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
	// Checks size and nb of rows and columns
	bool	isSameLayout(const Matrix &obj) const noexcept
	{ return (obj.getCols() == this->getCols() && obj.getRows() == this->getRows()); };
	// Checks only size
	bool	isSameSize(const Matrix &obj) const noexcept
	{ return (obj.getSize() == this->getSize()); };
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
	static bool	isVecSize(const Matrix &vec, const size_t size) noexcept
	{ return (Matrix::isVector(vec) && vec.getSize() == size); };
	static bool	isVec3(const Matrix &vec) noexcept
	{ return Matrix::isVecSize(vec, 3); };
	static bool	isVec4(const Matrix &vec) noexcept
	{ return Matrix::isVecSize(vec, 4); };
	// Checks size and nb of rows and columns
	static bool	isSameLayout(const Matrix &obj1, const Matrix &obj2) noexcept
	{ return (obj1.getCols() == obj2.getCols() && obj1.getRows() == obj2.getRows()); };
	// Checks only size
	static bool	isSameSize(const Matrix &obj1, const Matrix &obj2) noexcept
	{ return (obj1.getSize() == obj2.getSize()); };
	static bool	isEqual(const Matrix &obj1, const Matrix &obj2) noexcept;
	static bool	canMultiply(const Matrix &obj1, const Matrix &obj2) noexcept
	{ return (obj1.getRows() == obj2.getCols()); };

	static T	degToRad(const T deg) noexcept
	{ return (deg * (M_PI / 180)); };
	static T	radToDeg(const T rad) noexcept
	{ return (rad * (180 / M_PI)); };

	static Matrix	vec3(const T x, const T y, const T z);
	static T		vec2DLength(const Matrix &obj);
	static T		vec3DLength(const Matrix &obj);
	static T		vecLength(const Matrix &obj);

	static Matrix	normalize(const Matrix &obj);
	static Matrix	transpose(const Matrix &obj);
	static Matrix	average(const Matrix &obj1, const Matrix &obj2);
	static Matrix	compMult(const Matrix &obj1, const Matrix &obj2);
	static T		angle(const Matrix &vec1, const Matrix &vec2);
	static T		dot(const Matrix &vec1, const Matrix &vec2);
	static Matrix	cross(const Matrix &vec1, const Matrix &vec2);

	// Transformation

	static Matrix	scaling2D(const T x, const T y);
	static Matrix	scaling3D(const T x, const T y, const T z);
	static Matrix	scaling3D(const Matrix &vec3);

	static Matrix	rotation2D(const T angleInDegrees);
	static Matrix	rotationX3D(const T angleInDegrees);
	static Matrix	rotationY3D(const T angleInDegrees);
	static Matrix	rotationZ3D(const T angleInDegrees);
	static Matrix	rotation3D(const T angleInDegrees, const Matrix &axis);

	static Matrix	translation2D(const T x, const T y);
	static Matrix	translation3D(const T x, const T y, const T z);
	static Matrix	translation3D(const Matrix &vec3);

	// View

	static Matrix	lookAt(const Matrix &camPos, const Matrix &target,
		const Matrix &worldUp);

	// Projection

	static Matrix	orthographic(
		const float left, const float right,
		const float bottom, const float top,
		const float nearZ, const float farZ);
	static Matrix	perspective(
		const float fovY, const float aspectRatio,
		const float nearZ, const float farZ);
};

template <typename T>
Matrix<T>		operator*(const T n, const Matrix<T> &obj);
template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Matrix<T> &obj);

# include "Matrix.tpp"

#endif
