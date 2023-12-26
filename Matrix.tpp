/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:38:58 by thepaqui          #+#    #+#             */
/*   Updated: 2023/12/26 15:58:07 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_TPP
# define MATRIX_TPP

template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> data,
	const size_t rows, const size_t columns)
{
	if (data.size() / rows != columns)
		throw std::invalid_argument("Bad matrix size");
	_rows = rows;
	_columns = columns;
	_data.assign(data);
}

template <typename T>
void	Matrix<T>::print() const
{
	if (!_rows || !_columns)
		return ;
	for (size_t y = 0; y < _rows; y++) {
		std::cout << "| ";
		for (size_t x = 0; x < _columns; x++) {
			std::cout << _data[y * _columns + x] << ' ';
		}
		std::cout << "|\n";
	}
	std::cout << std::flush;
}

#endif