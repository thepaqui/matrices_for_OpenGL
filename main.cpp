/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:38:55 by thepaqui          #+#    #+#             */
/*   Updated: 2023/12/26 15:57:28 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.hpp"

int	main()
{
	Matrix<int>	myMat1( {
			2,	7,	9,
			5,	12,	1
		}, 2, 3);

	myMat1.print();
	
	return 0;
}