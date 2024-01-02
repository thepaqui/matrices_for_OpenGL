/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix4.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:39:03 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/02 15:42:42 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX4_HPP
# define MATRIX4_HPP
# include <iostream>
# include <vector>
# include <initializer_list>
# include <stdexcept>

template <typename T>
class Matrix4
{
private	:
	const size_t	_rows = 4;
	const size_t	_columns = 4;
	std::vector<T>	_data;

public	:
	Matrix4();
	Matrix4(const Matrix4 &obj);
	Matrix4(std::initializer_list<T> data);
	~Matrix4() {};

	inline size_t	getRows() const noexcept { return this->_rows; };
	inline size_t	getCols() const noexcept { return this->_columns; };
	inline const T	*getData() const noexcept { return this->_data.data(); };

	T		getElem(const uint8_t i, const uint8_t j) const;
	void	setElem(const uint8_t i, const uint8_t j, const T n);

	Matrix4		&operator=(const Matrix4 &obj);
	Matrix4		operator+(const Matrix4 &obj) const;
	Matrix4		operator-(const Matrix4 &obj) const;
	Matrix4		operator*(const T n) const;
	Matrix4		operator*(const Matrix4 &obj) const;

	Matrix4	transpose() const;
};

template <typename T>
Matrix4<T>		operator*(const T n, const Matrix4<T> &obj);
template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Matrix4<T> &obj);

# include "Matrix4.tpp"

#endif