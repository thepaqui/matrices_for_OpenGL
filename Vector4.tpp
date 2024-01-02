/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector4.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:56:39 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/02 16:12:50 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR4_TPP
# define VECTOR4_TPP
# include "Vector4.hpp"

// Constructors

template <typename T>
Vector4<T>::Vector4()
{
	std::initializer_list<T>	data = {
		1,
		1,
		1,
		1
	};
	this->_data.assign(data);
}

template <typename T>
Vector4<T>::Vector4(const Vector4<T> &obj)
{
	this->_data = obj._data;
}

template <typename T>
Vector4<T>::Vector4(std::initializer_list<T> data)
{
	if (data.size() != 4)
		throw std::invalid_argument("Bad initializer list size");
	this->_data.assign(data);
}

// Methods

template <typename T>
T	Vector4<T>::getElem(const uint8_t i) const
{
	if (i >= this->_rows)
		throw std::invalid_argument("Bad matrix access");
	return this->_data[i];
}

template <typename T>
void	Vector4<T>::setElem(const uint8_t i, const T n)
{
	if (i >= this->_rows)
		throw std::invalid_argument("Bad matrix access");
	this->_data[i] = n;
}

// Operator overloads

template <typename T>
Vector4<T>	&Vector4<T>::operator=(const Vector4<T> &obj)
{
	if (this != &obj)
		this->_data = obj._data;
	return (*this);
}

template <typename T>
Vector4<T>	Vector4<T>::operator+(const Vector4<T> &obj) const
{
	Vector4<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		ret._data[i] += obj._data[i];
	return ret;
}

template <typename T>
Vector4<T>	Vector4<T>::operator-(const Vector4<T> &obj) const
{
	Vector4<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		ret._data[i] -= obj._data[i];
	return ret;
}

template <typename T>
Vector4<T>	Vector4<T>::operator*(const T n) const
{
	Vector4<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		ret._data[i] *= n;
	return ret;
}

template <typename T>
Vector4<T>	operator*(const T n, const Vector4<T> &obj)
{
	Vector4<T>	ret;
	for (size_t i = 0; i < ret.getRows(); i++)
		ret.setElem(i, obj.getElem(i) * n);
	return ret;
}

template <typename T>
std::ostream	&operator<<(std::ostream &ostream, const Vector4<T> &obj)
{
	for (size_t i = 0; i < obj.getRows(); i++) {
		ostream << "| ";
		ostream << obj.getElem(i) << " ";
		ostream << "|\n";
	}
	ostream << std::flush;
	return (ostream);
}

#endif