/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:19:57 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/05 22:36:11 by thepaqui         ###   ########.fr       */
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

	Matrix<int>	id(4, 4, Mat_identity);
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

	Matrix<int>	mat1div2 = myMat1 / 2;
	std::cout << "Mat1 / 2\n" << mat1div2 << std::endl;

	Matrix<double>	myMat2(4, 4, {
		2.0,	7.0,	9.5,	3.1,
		5.0,	12.0,	1.5,	8.2,
		7.5,	11.0,	0.5,	10.0,
		4.2,	6.1,	13.13,	42.42
	});
	std::cout << "Mat2\n" << myMat2 << std::endl;

	Matrix<double>	mat2x3 = myMat2 * 3.0;
	std::cout << "Mat2 * 3.0\n" << mat2x3 << std::endl;

	Matrix<double>	mat2div2 = myMat2 / 2.0;
	std::cout << "Mat2 / 2.0\n" << mat2div2 << std::endl;

	Matrix<int>	myMat3(4, 4, {
		1,	8,	2,	10,
		4,	8,	40,	1,
		5,	1,	12,	6,
		6,	13,	37,	1
	});
	std::cout << "Mat3\n" << myMat3 << std::endl;

	Matrix<int>	mat3trans = Matrix<int>::transpose(myMat3);
	std::cout << "Mat3 (transposed)\n" << mat3trans << std::endl;

	Matrix<int>	mat1xmat3 = myMat1 * myMat3;
	std::cout << "Mat1 * Mat3\n" << mat1xmat3 << std::endl;

	Matrix<int>	mat3xmat1 = myMat3 * myMat1;
	std::cout << "Mat3 * Mat1\n" << mat3xmat1 << std::endl;

	Matrix<int>	mat1_3average = Matrix<int>::average(myMat1, myMat3);
	std::cout << "Average of Mat1 and Mat3\n" << mat1_3average << std::endl;

	Matrix<int>	myMat4(2, 3, {
		1,	8,	2,
		4,	8,	40
	});
	std::cout << "Mat4\n" << myMat4 << std::endl;

	Matrix<int>	mat4trans = Matrix<int>::transpose(myMat4);
	std::cout << "Mat4 (transposed)\n" << mat4trans << std::endl;

	Matrix<int>	myMat5(3, 2, {
		2,	7,
		5,	12,
		7,	11
	});
	std::cout << "Mat5\n" << myMat5 << std::endl;

	Matrix<int>	mat4xmat5 = myMat4 * myMat5;
	std::cout << "Mat4 * Mat5\n" << mat4xmat5 << std::endl;

	Matrix<int>	mat5xmat4 = myMat5 * myMat4;
	std::cout << "Mat5 * Mat4\n" << mat5xmat4 << std::endl;
}

void	testVectors()
{
	Matrix<int>	myVec1(4, 1, {
		6,
		9,
		18,
		1
	});
	std::cout << "Vec1\n" << myVec1;
	std::cout << "length = " << Matrix<int>::vec3DLength(myVec1) << "\n" << std::endl;

	Matrix<int>	id(4, 1, Mat_vector);
	std::cout << "id (default)\n" << id << std::endl;

	Matrix<int>	vec1plusid = myVec1 + id;
	std::cout << "Vec1 + id\n" << vec1plusid << std::endl;

	Matrix<int>	vec1minusid = myVec1 - id;
	std::cout << "Vec1 - id\n" << vec1minusid << std::endl;

	Matrix<int>	vec1x2 = 2 * myVec1;
	std::cout << "2 * Vec1\n" << vec1x2 << std::endl;

	Matrix<double>	myVec2(4, 1, {
		42.0,
		5.0,
		7.5,
		1.0
	});
	std::cout << "Vec2\n" << myVec2;
	std::cout << "length = " << Matrix<double>::vec3DLength(myVec2) << "\n" << std::endl;

	Matrix<double>	vec2x3 = myVec2 * 3.0;
	std::cout << "Vec2 * 3.0\n" << vec2x3 << std::endl;

	Matrix<double>	vec2trans = Matrix<double>::transpose(myVec2);
	std::cout << "Vec2 (transposed)\n" << vec2trans << std::endl;

	Matrix<double>	Scale1 = Matrix<double>::scaling3D(0.5, 2.5, 2.0);
	std::cout << "Scale1\n" << Scale1 << std::endl;

	Matrix<double>	scale1xvec2 = Scale1 * myVec2;
	std::cout << "Scale1 * Vec2\n" << scale1xvec2 << std::endl;

	Matrix<double>	Trans1 = Matrix<double>::translation3D(1.0, 5.0, -2.0);
	std::cout << "Trans1\n" << Trans1 << std::endl;

	Matrix<double>	trans1xvec2 = Trans1 * myVec2;
	std::cout << "Trans1 * Vec2\n" << trans1xvec2 << std::endl;

	Matrix<double>	Scale2 = Matrix<double>::scaling2D(2.0, 1.5);
	std::cout << "Scale2\n" << Scale2 << std::endl;

	Matrix<double>	Trans2 = Matrix<double>::translation2D(-0.5, -2.0);
	std::cout << "Trans2\n" << Trans2 << std::endl;

	Matrix<double>	myVec3(4, 1, {
		2.0,
		5.0,
		10.0,
		1.0
	});
	std::cout << "Vec3\n" << myVec3;
	std::cout << "length = " << Matrix<double>::vec3DLength(myVec3) << "\n" << std::endl;

	Matrix<double>	Rot1 = Matrix<double>::rotationX3D(-90.0);
	std::cout << "Rot1\n" << Rot1 << std::endl;

	Matrix<double>	rot1xvec3 = Rot1 * myVec3;
	std::cout << "Rot1 * Vec3\n" << rot1xvec3 << std::endl;

	Matrix<double>	Rot2 = Matrix<double>::rotationY3D(-90.0);
	std::cout << "Rot2\n" << Rot2 << std::endl;

	Matrix<double>	rot2xvec3 = Rot2 * myVec3;
	std::cout << "Rot2 * Vec3\n" << rot2xvec3 << std::endl;

	Matrix<double>	Rot3 = Matrix<double>::rotationZ3D(-90.0);
	std::cout << "Rot3\n" << Rot3 << std::endl;

	Matrix<double>	rot3xvec3 = Rot3 * myVec3;
	std::cout << "Rot3 * Vec3\n" << rot3xvec3 << std::endl;

	Matrix<double>	Rot4 = Matrix<double>::rotation3D(-90.0,
		Matrix<double>::axis(0.662, 0.2, 0.722)); // Rotation axis
	std::cout << "Rot4\n" << Rot4 << std::endl;

	Matrix<double>	rot4xvec3 = Rot4 * myVec3;
	std::cout << "Rot4 * Vec3\n" << rot4xvec3 << std::endl;

	Matrix<float>	myVec4(3, 1, {
		4.3f,
		5.7f,
		-8.12f
	});
	std::cout << "Vec4\n" << myVec4;
	std::cout << "length = " << Matrix<float>::vec3DLength(myVec4) << "\n" << std::endl;

	Matrix<float>	myVec5(3, 1, {
		-2.7f,
		4.5f,
		10.1f
	});
	std::cout << "Vec5\n" << myVec5;
	std::cout << "length = " << Matrix<float>::vec3DLength(myVec5) << "\n" << std::endl;

	float	angleV4V5 = Matrix<float>::angle(myVec4, myVec5);
	float	angleV5V4 = Matrix<float>::angle(myVec5, myVec4);
	std::cout << "Angle between Vec4 and Vec5 = " << angleV4V5 << std::endl;
	std::cout << "Angle between Vec5 and Vec4 = " << angleV5V4 << std::endl;
	float	dotV4V5 = Matrix<float>::dot(myVec4, myVec5);
	float	dotV5V4 = Matrix<float>::dot(myVec5, myVec4);
	std::cout << "Vec4 . Vec5 = " << dotV4V5 << std::endl;
	std::cout << "Vec5 . Vec4 = " << dotV5V4 << std::endl;
	Matrix<float>	crossV4V5 = Matrix<float>::cross(myVec4, myVec5);
	Matrix<float>	crossV5V4 = Matrix<float>::cross(myVec5, myVec4);
	std::cout << "Vec4 x Vec5\n" << crossV4V5;
	std::cout << "Vec5 x Vec4\n" << crossV5V4 << std::endl;
}
