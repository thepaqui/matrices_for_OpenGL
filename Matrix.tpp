/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:38:58 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/04 01:25:38 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_TPP
# define MATRIX_TPP
# include "Matrix.hpp"

// Constructors

// Unspecified type is MAT_REGULAR
// MAT_REGULAR fills with 0s
// MAT_VECTOR fills with 1s
// MAT_IDENTITY creates an identity matrix of given size if possible
template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns, Mat_type type)
: _rows(rows), _columns(columns)
{
	if (type != MAT_REGULAR && type != MAT_VECTOR && type != MAT_IDENTITY)
		throw std::invalid_argument("Invalid matrix type");

	if (this->getRows() == 0 || this->getCols() == 0)
		throw std::invalid_argument("Matrix can't have size of 0");

	if (type == MAT_VECTOR && Matrix::isVector(*this) == false)
		throw std::invalid_argument("Invalid vector size");

	if (type == MAT_IDENTITY)
	{
		if (this->getRows() != this->getCols())
			throw std::invalid_argument("Identity matrix needs to be square");
		for (size_t i = 0; i < this->getRows(); i++)
		{
			for (size_t j = 0; j < this->getCols(); j++)
			{
				if (i == j)
					_data.push_back(1);
				else
					_data.push_back(0);
			}
		}
		return ;
	}

	size_t	size = this->getCols() * this->getRows();
	if (type == MAT_VECTOR)
		_data.assign(size, 1);
	else
		_data.assign(size, 0);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &obj)
: _rows(obj.getRows()), _columns(obj.getCols())
{
	if (this->getRows() == 0 || this->getCols() == 0)
		throw std::invalid_argument("Matrix can't have size of 0");
	this->_data = obj._data;
}

template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns,
	std::initializer_list<T> data)
: _rows(rows), _columns(columns)
{
	if (this->getRows() == 0 || this->getCols() == 0)
		throw std::invalid_argument("Matrix can't have size of 0");
	if (data.size() / this->getCols() != this->getRows()
		|| data.size() % this->getCols() != 0)
		throw std::invalid_argument("Bad initializer list size");
	this->_data.assign(data);
}

// Methods

template <typename T>
T	Matrix<T>::getElem(const uint8_t i, const uint8_t j) const
{
	if (i >= this->getRows() || j >= this->getCols())
		throw std::out_of_range("Matrix read access out of range");
	return this->_data[index(i,j)];
}

template <typename T>
void	Matrix<T>::setElem(const uint8_t i, const uint8_t j, const T n)
{
	if (i >= this->getRows() || j >= this->getCols())
		throw std::out_of_range("Matrix write access out of range");
	this->_data[index(i,j)] = n;
}

// Operator overloads

template <typename T>
Matrix<T>	&Matrix<T>::operator=(const Matrix<T> &obj)
{
	if (this == &obj)
		return (*this);
	if (this->isSameSize(obj) == false)
		throw std::runtime_error("Mismatched matrix sizes when copying (assignment)");
	this->_data = obj._data;
	return (*this);
}

template <typename T>
Matrix<T>	Matrix<T>::operator+(const Matrix<T> &obj) const
{
	if (this->isSameSize(obj) == false)
		throw std::runtime_error("Mismatched matrix sizes when adding");

	Matrix<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret._data[index(i,j)] += obj._data[index(i,j)];
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::operator-(const Matrix<T> &obj) const
{
	if (this->isSameSize(obj) == false)
		throw std::runtime_error("Mismatched matrix sizes when subtracting");

	Matrix<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret._data[index(i,j)] -= obj._data[index(i,j)];
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::operator*(const T n) const
{
	Matrix<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret._data[index(i,j)] *= n;
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::operator*(const Matrix &obj) const
{
	if (this->canMultiply(obj) == false)
		throw std::runtime_error("Mismatched matrix sizes when multiplying");

	Matrix<T>	ret(this->getRows(), obj.getCols());
	for (size_t i = 0; i < ret.getRows(); i++)
	{
		for (size_t j = 0; j < ret.getCols(); j++)
		{
			T	val = 0;
			for (size_t p = 0; p < this->getCols(); p++)
				val += this->getElem(i, p) * obj.getElem(p, j);
			ret.setElem(i, j, val);
		}
	}
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::operator/(const T n) const
{
	Matrix<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret._data[index(i,j)] /= n;
	return ret;
}

template <typename T>
Matrix<T>	operator*(const T n, const Matrix<T> &obj)
{
	Matrix<T>	ret(obj.getRows(), obj.getCols());
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret.setElem(i, j, obj.getElem(i, j) * n);
	return ret;
}

template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Matrix<T> &obj)
{
	for (size_t i = 0; i < obj.getRows(); i++) {
		ostream << "| ";
		for (size_t j = 0; j < obj.getCols(); j++) {
			ostream << obj.getElem(i, j) << " ";
		}
		ostream << "|\n";
	}
	ostream << std::flush;
	return (ostream);
}

// Others

template <typename T>
T	Matrix<T>::vec2DLength(const Matrix &obj)
{
	if (Matrix::isVector(obj) == false)
		throw std::invalid_argument("Can only get length from a vector");
	size_t	dimensions = obj.getCols() * obj.getRows();
	if (dimensions < 2 || dimensions > 3)
		throw std::invalid_argument("Bad 2D vector size (2 or 3 only)");

	const T	*coordinates = obj.getData();
	T	length = 0;
	for (size_t i = 0; i < 2; i++)
		length += coordinates[i] * coordinates[i];
	length = sqrt(length);

	return length;
}

template <typename T>
T	Matrix<T>::vec3DLength(const Matrix &obj)
{
	if (Matrix::isVector(obj) == false)
		throw std::invalid_argument("Can only get length from a vector");
	size_t	dimensions = obj.getCols() * obj.getRows();
	if (dimensions < 3 || dimensions > 4)
		throw std::invalid_argument("Bad 3D vector size (3 or 4 only)");

	const T	*coordinates = obj.getData();
	T	length = 0;
	for (size_t i = 0; i < 3; i++)
		length += coordinates[i] * coordinates[i];
	length = sqrt(length);

	return length;
}

template <typename T>
Matrix<T>	Matrix<T>::transpose(const Matrix &obj)
{
	Matrix	ret(obj.getCols(), obj.getRows());
	for (size_t i = 0; i < obj.getRows(); i++)
		for (size_t j = 0; j < obj.getCols(); j++)
			ret.setElem(j, i, obj.getElem(i, j));
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::average(const Matrix &obj1, const Matrix &obj2)
{
	if (Matrix::isSameSize(obj1, obj2) == false)
		throw std::invalid_argument("Cannot get average of matrices of different sizes");
	Matrix	ret = (obj1 + obj2) / 2;
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::scaling(const T x, const T y)
{
	Matrix	ret(3, 3, MAT_IDENTITY);
	ret.setElem(0, 0, x);
	ret.setElem(1, 1, y);
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::scaling(const T x, const T y, const T z)
{
	Matrix	ret(4, 4, MAT_IDENTITY);
	ret.setElem(0, 0, x);
	ret.setElem(1, 1, y);
	ret.setElem(2, 2, z);
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::translation(const T x, const T y)
{
	Matrix	ret(3, 3, MAT_IDENTITY);
	ret.setElem(0, 2, x);
	ret.setElem(1, 2, y);
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::translation(const T x, const T y, const T z)
{
	Matrix	ret(4, 4, MAT_IDENTITY);
	ret.setElem(0, 3, x);
	ret.setElem(1, 3, y);
	ret.setElem(2, 3, z);
	return ret;
}

#endif