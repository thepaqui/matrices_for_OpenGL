/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector4.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:56:40 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/02 16:12:46 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR4_HPP
# define VECTOR4_HPP
# include <iostream>
# include <vector>
# include <initializer_list>
# include <stdexcept>

// 4 rows, 1 column
template <typename T>
class Vector4
{
private	:
	const size_t	_rows = 4;
	const size_t	_columns = 1;
	std::vector<T>	_data;

public	:
	Vector4();
	Vector4(const Vector4 &obj);
	Vector4(std::initializer_list<T> data);
	~Vector4() {};

	inline size_t	getRows() const noexcept { return this->_rows; };
	inline size_t	getCols() const noexcept { return this->_columns; };
	inline const T	*getData() const noexcept { return this->_data.data(); };

	T		getElem(const uint8_t i) const;
	void	setElem(const uint8_t i, const T n);

	Vector4		&operator=(const Vector4 &obj);
	Vector4		operator+(const Vector4 &obj) const;
	Vector4		operator-(const Vector4 &obj) const;
	Vector4		operator*(const T n) const;
};

template <typename T>
Vector4<T>		operator*(const T n, const Vector4<T> &obj);
template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Vector4<T> &obj);

# include "Vector4.tpp"

#endif