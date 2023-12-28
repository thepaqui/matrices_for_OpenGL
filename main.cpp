/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:38:55 by thepaqui          #+#    #+#             */
/*   Updated: 2023/12/28 01:55:43 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix4.hpp"

int	main()
{
	Matrix4<int>	myMat1({
		2,	7,	9,	3,
		5,	12,	1,	8,
		7,	11,	0,	10,
		4,	6,	13,	42
	});

	Matrix4<int>	id;

	Matrix4<double>	myMat2({
		2.0,	7.0,	9.5,	3.1,
		5.0,	12.0,	1.5,	8.2,
		7.5,	11.0,	0.5,	10.0,
		4.2,	6.1,	13.13,	42.42
	});

	Matrix4<int>	mat1plusid = myMat1 + id;
	Matrix4<int>	mat1minusid = myMat1 - id;

	std::cout << myMat1.getRows() << " " << myMat1.getCols() << std::endl
		<< myMat1 << std::endl
		<< id << std::endl
		<< mat1plusid << std::endl
		<< mat1minusid << std::endl
		<< myMat2;

	return 0;
}