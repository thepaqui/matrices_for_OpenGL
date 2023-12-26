/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:39:03 by thepaqui          #+#    #+#             */
/*   Updated: 2023/12/26 15:55:06 by thepaqui         ###   ########.fr       */
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
	size_t			_rows = 4;
	size_t			_columns = 4;
	std::vector<T>	_data;

public	:
	Matrix();
	Matrix(std::initializer_list<T> data,
		const size_t rows, const size_t columns);
	~Matrix() {}

	void	print() const;

	inline size_t	getRows() const { return this->_rows; }
	inline size_t	getCols() const { return this->_columns; }
	inline const T	*getData() const noexcept { return this->_data.data(); }
};

# include "Matrix.tpp"

#endif