/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:38:58 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/02 22:50:03 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_TPP
# define MATRIX_TPP
# include "Matrix.hpp"

// Constructors

template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns)
: _rows(rows), _columns(columns)
{
	if (this->getRows() == 0 || this->getCols() == 0)
		throw std::invalid_argument("Matrix can't have size of 0");
	if (this->getRows() == 4 && this->getCols() == 1)
		_data.assign({1, 1, 1, 1});
	else if (this->getRows() != this->getCols())
		throw std::invalid_argument("Identity Matrix needs to be square");
	else
	{
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
	}
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
Matrix<T>::Matrix(const size_t rows, const size_t columns, std::initializer_list<T> data)
: _rows(rows), _columns(columns)
{
	if (this->getRows() == 0 || this->getCols() == 0)
		throw std::invalid_argument("Matrix can't have size of 0");
	if (data.size() / this->getCols() != this->getRows())
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
		throw std::runtime_error("Mismatched Matrix sizes when copying (assignment)");
	this->_data = obj._data;
	return (*this);
}

template <typename T>
Matrix<T>	Matrix<T>::operator+(const Matrix<T> &obj) const
{
	if (this->isSameSize(obj) == false)
		throw std::runtime_error("Mismatched Matrix sizes when adding");

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
		throw std::runtime_error("Mismatched Matrix sizes when subtracting");

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
		throw std::runtime_error("Mismatched Matrix sizes when multiplying");

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
Matrix<T>	Matrix<T>::transpose() const
{
	Matrix	ret(this->getCols(), this->getRows());
	for (size_t i = 0; i < this->getRows(); i++)
		for (size_t j = 0; j < this->getCols(); j++)
			ret.setElem(j, i, this->getElem(i, j));
	return ret;
}

#endif