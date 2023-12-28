/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix4.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:38:58 by thepaqui          #+#    #+#             */
/*   Updated: 2023/12/28 01:55:02 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX4_TPP
# define MATRIX4_TPP
# include "Matrix4.hpp"

/* Matrix4 */

template <typename T>
Matrix4<T>::Matrix4()
{
	std::initializer_list<T>	data = {
		1,	0,	0,	0,
		0,	1,	0,	0,
		0,	0,	1,	0,
		0,	0,	0,	1
	};
	this->_data.assign(data);
}

template <typename T>
Matrix4<T>::Matrix4(const Matrix4<T> &obj)
{
	this->_data = obj._data;
}

template <typename T>
Matrix4<T>::Matrix4(std::initializer_list<T> data)
{
	if (data.size() != 16)
		throw std::invalid_argument("Bad initializer list size");
	this->_data.assign(data);
}

template <typename T>
Matrix4<T>	&Matrix4<T>::operator=(const Matrix4<T> &obj)
{
	if (this != &obj)
		this->_data = obj._data;
	return (*this);
}

template <typename T>
Matrix4<T>	Matrix4<T>::operator+(const Matrix4<T> &obj) const
{
	Matrix4<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret._data[i * ret.getCols() + j] += obj._data[i * ret.getCols() + j];
	return ret;
}

template <typename T>
Matrix4<T>	Matrix4<T>::operator-(const Matrix4<T> &obj) const
{
	Matrix4<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret._data[i * ret.getCols() + j] -= obj._data[i * ret.getCols() + j];
	return ret;
}

template <typename T>
T	Matrix4<T>::getElem(const uint8_t i, const uint8_t j) const
{
	if (i >= this->_rows || j >= this->_columns)
		throw std::invalid_argument("Bad matrix access");
	return this->_data[i * this->_columns + j];
}

template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Matrix4<T> &obj)
{
	for (size_t i = 0; i < obj.getRows(); i++) {
		ostream << "|  ";
		for (size_t j = 0; j < obj.getCols(); j++) {
			ostream << obj.getElem(i, j) << "  ";
		}
		ostream << "|\n";
	}
	ostream << std::flush;
	return (ostream);
}

#endif