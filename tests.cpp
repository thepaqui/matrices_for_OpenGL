/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:19:57 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/02 23:47:40 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.hpp"

void	testMatrices()
{
	Matrix<int>	myMat1(4, 4, {
		2,	7,	9,	3,
		5,	12,	1,	8,
		7,	11,	0,	10,
		4,	6,	13,	42
	});
	std::cout << "Mat1\n" << myMat1 << std::endl;

	Matrix<int>	id(4, 4, MAT_IDENTITY);
	std::cout << "id (default)\n" << id << std::endl;

	Matrix<int>	mat1plusid = myMat1 + id;
	std::cout << "Mat1 + id\n" << mat1plusid << std::endl;

	Matrix<int>	mat1minusid = myMat1 - id;
	std::cout << "Mat1 - id\n" << mat1minusid << std::endl;

	Matrix<int>	mat1x2 = 2 * myMat1;
	std::cout << "2 * Mat1\n" << mat1x2 << std::endl;

	Matrix<int>	mat1xid = myMat1 * id;
	std::cout << "Mat1 * id\n" << mat1xid << std::endl;

	Matrix<int>	idxmat1 = id * myMat1;
	std::cout << "id * Mat1\n" << idxmat1 << std::endl;

	Matrix<double>	myMat2(4, 4, {
		2.0,	7.0,	9.5,	3.1,
		5.0,	12.0,	1.5,	8.2,
		7.5,	11.0,	0.5,	10.0,
		4.2,	6.1,	13.13,	42.42
	});
	std::cout << "Mat2\n" << myMat2 << std::endl;

	Matrix<double>	mat2x3 = myMat2 * 3.0;
	std::cout << "Mat2 * 3.0\n" << mat2x3 << std::endl;

	Matrix<int>	myMat3(4, 4, {
		1,	8,	2,	10,
		4,	8,	40,	1,
		5,	1,	12,	6,
		6,	13,	37,	1
	});
	std::cout << "Mat3\n" << myMat3 << std::endl;

	Matrix<int>	mat1xmat3 = myMat1 * myMat3;
	std::cout << "Mat1 * Mat3\n" << mat1xmat3 << std::endl;

	Matrix<int>	mat3xmat1 = myMat3 * myMat1;
	std::cout << "Mat3 * Mat1\n" << mat3xmat1 << std::endl;

	Matrix<int>	mat3trans = myMat3.transpose();
	std::cout << "Mat3 (transposed)\n" << mat3trans << std::endl;

	Matrix<int>	myMat4(2, 3, {
		1,	8,	2,
		4,	8,	40
	});
	std::cout << "Mat4\n" << myMat4 << std::endl;

	Matrix<int>	mat4trans = myMat4.transpose();
	std::cout << "Mat4 (transposed)\n" << mat4trans << std::endl;

	myMat1 = myMat4;
}

void	testVectors()
{
	Matrix<int>	myVec1(4, 1, {
		6,
		9,
		18,
		1
	});
	std::cout << "Vec1\n" << myVec1 << std::endl;

	Matrix<int>	id(4, 1, MAT_VECTOR);
	std::cout << "id (default)\n" << id << std::endl;

	Matrix<int>	vec1plusid = myVec1 + id;
	std::cout << "Vec1 + id\n" << vec1plusid << std::endl;

	Matrix<int>	vec1minusid = myVec1 - id;
	std::cout << "Vec1 - id\n" << vec1minusid << std::endl;

	Matrix<int>	vec1x2 = 2 * myVec1;
	std::cout << "2 * Vec1\n" << vec1x2 << std::endl;

	Matrix<double>	myVec2(4, 1, {
		2.0,
		5.0,
		7.5,
		4.2
	});
	std::cout << "Vec2\n" << myVec2 << std::endl;

	Matrix<double>	vec2x3 = myVec2 * 3.0;
	std::cout << "Vec2 * 3.0\n" << vec2x3 << std::endl;

	Matrix<double>	vec2trans = myVec2.transpose();
	std::cout << "Vec2 (transposed)\n" << vec2trans << std::endl;
}
