/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:01:45 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/02 22:27:49 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP
# include <iostream>
# include <vector>
# include <initializer_list>
# include <stdexcept>

template <typename T>
class Matrix
{
private	:
	const size_t	_rows;
	const size_t	_columns;
	std::vector<T>	_data;

	inline size_t	index(const uint8_t i, const uint8_t j) const noexcept
	{ return (i * this->_columns + j); };

public	:
	Matrix(const size_t rows, const size_t columns);
	Matrix(const Matrix &obj);
	Matrix(const size_t rows, const size_t columns, std::initializer_list<T> data);
	~Matrix() {};

	inline size_t	getRows() const noexcept { return this->_rows; };
	inline size_t	getCols() const noexcept { return this->_columns; };
	inline const T	*getData() const noexcept { return this->_data.data(); };
	inline bool		isSameSize(const Matrix &obj) const noexcept
	{ return (obj.getCols() == this->getCols() && obj.getRows() == this->getRows()); };
	inline bool		canMultiply(const Matrix &obj) const noexcept
	{ return (obj.getRows() == this->getCols()); };

	T		getElem(const uint8_t i, const uint8_t j) const;
	void	setElem(const uint8_t i, const uint8_t j, const T n);

	Matrix		&operator=(const Matrix &obj);
	Matrix		operator+(const Matrix &obj) const;
	Matrix		operator-(const Matrix &obj) const;
	Matrix		operator*(const T n) const;
	Matrix		operator*(const Matrix &obj) const;

	Matrix	transpose() const;
};

template <typename T>
Matrix<T>		operator*(const T n, const Matrix<T> &obj);
template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Matrix<T> &obj);

# include "Matrix.tpp"

#endif