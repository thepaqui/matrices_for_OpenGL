/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:38:58 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/05 23:48:35 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_TPP
# define MATRIX_TPP
# include "Matrix.hpp"

// Constructors

// Unspecified type picks Mat_null
// Mat_null fills with 0s
// Mat_vector fills with 1s and checks dimensions (Nx1 or 1xM)
// Mat_identity creates an identity matrix and checks dimensions (square)
template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns, const Mat_type type)
: _rows(rows), _columns(columns)
{
	if (type != Mat_null && type != Mat_vector && type != Mat_identity)
		throw std::invalid_argument("Invalid matrix type");

	if (this->getRows() == 0 || this->getCols() == 0)
		throw std::invalid_argument("Matrix can't have size of 0");

	if (type == Mat_vector && Matrix::isVector(*this) == false)
		throw std::invalid_argument("Invalid vector size");

	if (type == Mat_identity)
	{
		if (this->getRows() != this->getCols())
			throw std::invalid_argument("Identity matrix needs to be square");
		for (size_t i = 0; i < this->getRows(); i++)
		{
			for (size_t j = 0; j < this->getCols(); j++)
			{
				if (i == j)
					this->_data.push_back(1);
				else
					this->_data.push_back(0);
			}
		}
		return ;
	}

	size_t	size = this->getSize();
	if (type == Mat_vector)
		this->_data.assign(size, 1);
	else
		this->_data.assign(size, 0);
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
	const std::initializer_list<T> data)
: _rows(rows), _columns(columns)
{
	if (this->getRows() == 0 || this->getCols() == 0)
		throw std::invalid_argument("Matrix can't have size of 0");
	if (data.size() / this->getCols() != this->getRows()
		|| data.size() % this->getCols() != 0)
		throw std::invalid_argument("Bad initializer list size");
	this->_data.assign(data);
}

// Creates a column vector
// Vec_point creates a vector (x, y, z, 1)
// Vec_axis creates a vector (x, y, z)
template <typename T>
Matrix<T>::Matrix(const T x, const T y, const T z, const Vec_type type)
: _rows(3 + type), _columns(1)
{
	if (type != Vec_point && type != Vec_axis)
		throw std::invalid_argument("Invalid vector type");
	this->_data.push_back(x);
	this->_data.push_back(y);
	this->_data.push_back(z);
	if (type == Vec_point)
		this->_data.push_back(1);
}

// Methods

template <typename T>
T	Matrix<T>::getElem(const size_t i, const size_t j) const
{
	if (i >= this->getRows() || j >= this->getCols())
		throw std::out_of_range("Matrix read access out of range");
	return this->_data[index(i,j)];
}

template <typename T>
T	Matrix<T>::getElem(const size_t ind) const
{
	if (ind >= this->getSize())
		throw std::out_of_range("Matrix read access out of range");
	return this->_data[ind];
}

template <typename T>
void	Matrix<T>::setElem(const size_t i, const size_t j, const T n)
{
	if (i >= this->getRows() || j >= this->getCols())
		throw std::out_of_range("Matrix write access out of range");
	this->_data[index(i,j)] = n;
}

template <typename T>
void	Matrix<T>::setElem(const size_t ind, const T n)
{
	if (ind >= this->getSize())
		throw std::out_of_range("Matrix write access out of range");
	this->_data[ind] = n;
}

// Operator overloads

template <typename T>
Matrix<T>	&Matrix<T>::operator=(const Matrix<T> &obj)
{
	if (this == &obj)
		return (*this);
	if (this->isSameLayout(obj) == false)
		throw std::runtime_error("Mismatched matrix layouts when copying (assignment)");
	this->_data = obj._data;
	return (*this);
}

template <typename T>
Matrix<T>	Matrix<T>::operator+(const Matrix<T> &obj) const
{
	if (this->isSameLayout(obj) == false)
		throw std::runtime_error("Mismatched matrix layouts when adding");

	Matrix<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret._data[index(i,j)] += obj.getElem(i,j);
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::operator-(const Matrix<T> &obj) const
{
	if (this->isSameLayout(obj) == false)
		throw std::runtime_error("Mismatched matrix layouts when subtracting");

	Matrix<T>	ret(*this);
	for (size_t i = 0; i < ret.getRows(); i++)
		for (size_t j = 0; j < ret.getCols(); j++)
			ret._data[index(i,j)] -= obj.getElem(i,j);
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

// Also checks if both matrices have the same layout
template <typename T>
bool	Matrix<T>::isEqual(const Matrix<T> &obj1, const Matrix<T> &obj2) noexcept
{
	if (Matrix::isSameLayout(obj1, obj2) == false)
		return false;

	size_t	size = obj1.getSize();
	for (size_t i = 0; i < size; i++)
		if (obj1.getElem(i) != obj2.getElem(i))
			return false;

	return true;
}

template <typename T>
Matrix<T>	Matrix<T>::vec3(const T x, const T y, const T z)
{
	Matrix	ret(x, y, z, Vec_axis);

	return ret;
}

// Ignores 3rd coordinate if present
template <typename T>
T	Matrix<T>::vec2DLength(const Matrix &obj)
{
	if (Matrix::isVector(obj) == false)
		throw std::invalid_argument("Can only get length from a vector");
	size_t	dimensions = obj.getSize();
	if (dimensions < 2 || dimensions > 3)
		throw std::invalid_argument("Bad 2D vector size (2 or 3 only)");

	T	length = 0;
	for (size_t i = 0; i < 2; i++)
		length += obj.getElem(i) * obj.getElem(i);
	length = sqrt(length);

	return length;
}

// Ignores 4th coordinate if present
template <typename T>
T	Matrix<T>::vec3DLength(const Matrix &obj)
{
	if (Matrix::isVector(obj) == false)
		throw std::invalid_argument("Can only get length from a vector");
	size_t	dimensions = obj.getSize();
	if (dimensions < 3 || dimensions > 4)
		throw std::invalid_argument("Bad 3D vector size (3 or 4 only)");

	T	length = 0;
	for (size_t i = 0; i < 3; i++)
		length += obj.getElem(i) * obj.getElem(i);
	length = sqrt(length);

	return length;
}

template <typename T>
T	Matrix<T>::vecLength(const Matrix &obj)
{
	if (Matrix::isVector(obj) == false)
		throw std::invalid_argument("Can only get length from a vector");
	size_t	dimensions = obj.getSize();

	T	length = 0;
	for (size_t i = 0; i < dimensions; i++)
		length += obj.getElem(i) * obj.getElem(i);
	length = sqrt(length);

	return length;
}

template <typename T>
Matrix<T>	Matrix<T>::normalize(const Matrix &obj)
{
	if (Matrix::isVector(obj) == false)
		throw std::invalid_argument("Can't normalize non-vector matrix");

	return (obj / Matrix::vecLength(obj));
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
	if (Matrix::isSameLayout(obj1, obj2) == false)
		throw std::invalid_argument("Cannot get average of matrices of different layouts");
	Matrix	ret = (obj1 + obj2) / 2;
	return ret;
}

// Returns angle in degrees
template <typename T>
T	Matrix<T>::angle(const Matrix &vec1, const Matrix &vec2)
{
	if (Matrix::isVector(vec1) == false || Matrix::isVector(vec2) == false)
		throw std::invalid_argument("Can only get angle from vectors");
	if (Matrix::isSameSize(vec1, vec2) == false)
		throw std::invalid_argument("Cannot get angle of vectors of different sizes");
	if (vec1.getSize() != 3 && vec1.getSize() != 2)
		throw std::invalid_argument("Angle only defined for 2D or 3D vectors");

	T	ret = Matrix::dot(vec1, vec2) / (Matrix::vecLength(vec1) * Matrix::vecLength(vec2));
	ret = Matrix::radToDeg(acos(ret));

	return ret;
}

template <typename T>
T	Matrix<T>::dot(const Matrix &vec1, const Matrix &vec2)
{
	if (Matrix::isVector(vec1) == false || Matrix::isVector(vec2) == false)
		throw std::invalid_argument("Dot product only takes vectors");
	if (Matrix::isSameSize(vec1, vec2) == false)
		throw std::invalid_argument("Cannot get dot product of vectors of different sizes");

	size_t	size = vec1.getSize();

	T	ret = 0;
	for (size_t i = 0; i < size; i++)
		ret += vec1.getElem(i) * vec2.getElem(i);

	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::cross(const Matrix &vec1, const Matrix &vec2)
{
	if (Matrix::isVector(vec1) == false || Matrix::isVector(vec2) == false)
		throw std::invalid_argument("Cross product only takes vectors");
	if (Matrix::isSameSize(vec1, vec2) == false)
		throw std::invalid_argument("Cannot get cross product of vectors of different sizes");
	if (vec1.getSize() != 3)
		throw std::invalid_argument("Cross product only defined for 3D vectors");

	const T	x1 = vec1.getElem(0);
	const T	y1 = vec1.getElem(1);
	const T	z1 = vec1.getElem(2);
	const T	x2 = vec2.getElem(0);
	const T	y2 = vec2.getElem(1);
	const T	z2 = vec2.getElem(2);

	Matrix	ret(3, 1, Mat_null);
	ret.setElem(0, (y1 * z2) - (z1 * y2));
	ret.setElem(1, (z1 * x2) - (x1 * z2));
	ret.setElem(2, (x1 * y2) - (y1 * x2));

	return ret;
}

// Transformations

template <typename T>
Matrix<T>	Matrix<T>::scaling2D(const T x, const T y)
{
	Matrix	ret(3, 3, Mat_identity);
	ret.setElem(0, x);
	ret.setElem(4, y);
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::scaling3D(const T x, const T y, const T z)
{
	Matrix	ret(4, 4, Mat_identity);
	ret.setElem(0, x);
	ret.setElem(5, y);
	ret.setElem(10, z);
	return ret;
}

// 2D rotation (counter-clockwise)
template <typename T>
Matrix<T>	Matrix<T>::rotation2D(const T angleInDegrees)
{
	T	rad = Matrix::degToRad(angleInDegrees);
	Matrix	ret(3, 3, Mat_identity);
	ret.setElem(0, cos(rad));
	ret.setElem(1, -sin(rad));
	ret.setElem(3, sin(rad));
	ret.setElem(4, cos(rad));
	return ret;
}

// 3D rotation around the X axis (counter-clockwise ?)
template <typename T>
Matrix<T>	Matrix<T>::rotationX3D(const T angleInDegrees)
{
	T	rad = Matrix::degToRad(angleInDegrees);
	Matrix	ret(4, 4, Mat_identity);
	ret.setElem(5, cos(rad));
	ret.setElem(6, -sin(rad));
	ret.setElem(9, sin(rad));
	ret.setElem(10, cos(rad));
	return ret;
}

// 3D rotation around the Y axis (counter-clockwise ?)
template <typename T>
Matrix<T>	Matrix<T>::rotationY3D(const T angleInDegrees)
{
	T	rad = Matrix::degToRad(angleInDegrees);
	Matrix	ret(4, 4, Mat_identity);
	ret.setElem(0, cos(rad));
	ret.setElem(2, sin(rad));
	ret.setElem(8, -sin(rad));
	ret.setElem(10, cos(rad));
	return ret;
}

// 3D rotation around the Z axis (counter-clockwise ?)
template <typename T>
Matrix<T>	Matrix<T>::rotationZ3D(const T angleInDegrees)
{
	T	rad = Matrix::degToRad(angleInDegrees);
	Matrix	ret(4, 4, Mat_identity);
	ret.setElem(0, cos(rad));
	ret.setElem(1, -sin(rad));
	ret.setElem(4, sin(rad));
	ret.setElem(5, cos(rad));
	return ret;
}

// 3D rotation around the given axis (counter-clockwise ?)
// axis is a 3D vector and does not need to be normalized beforehand
template <typename T>
Matrix<T>	Matrix<T>::rotation3D(const T angleInDegrees, const Matrix &axis)
{
	if (Matrix::isVector(axis) == false || axis.getSize() != 3)
		throw std::invalid_argument("Bad rotation axis");

	Matrix	naxis = Matrix::normalize(axis);
	T		rx = naxis.getElem(0);
	T		ry = naxis.getElem(1);
	T		rz = naxis.getElem(2);

	T		rad = Matrix::degToRad(angleInDegrees);
	double	_cos = cos(rad);
	double	_sin = sin(rad);
	double	_icos = 1 - _cos;

	Matrix	ret(4, 4, Mat_identity);
	ret.setElem(0, _cos + (rx * rx * _icos));
	ret.setElem(1, (rx * ry * _icos) - (rz * _sin));
	ret.setElem(2, (rx * rz * _icos) + (ry * _sin));

	ret.setElem(4, (ry * rx * _icos) + (rz * _sin));
	ret.setElem(5, _cos + (ry * ry * _icos));
	ret.setElem(6, (ry * rz * _icos) - (rx * _sin));

	ret.setElem(8, (rz * rx * _icos) - (ry * _sin));
	ret.setElem(9, (rz * ry * _icos) + (rx * _sin));
	ret.setElem(10, _cos + (rz * rz * _icos));

	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::translation2D(const T x, const T y)
{
	Matrix	ret(3, 3, Mat_identity);
	ret.setElem(2, x);
	ret.setElem(5, y);
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::translation3D(const T x, const T y, const T z)
{
	Matrix	ret(4, 4, Mat_identity);
	ret.setElem(3, x);
	ret.setElem(7, y);
	ret.setElem(11, z);
	return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::lookAt(const Matrix<T> &camPos, const Matrix<T> &target,
	const Matrix<T> &worldUp)
{
	
}

#endif