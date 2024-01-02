/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:38:55 by thepaqui          #+#    #+#             */
/*   Updated: 2024/01/02 16:39:15 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>

void	testMatrices();
void	testVectors();

#define OPTION_ALL 0
#define OPTION_MAT 1
#define OPTION_VEC 2

int	usage()
{
	std::cout << "Usage:\n"
		<< "$> ./Matrix\n"
		<< "...all tests...\n\n"
		<< "$> ./Matrix <OPTION>\n"
		<< "...tests defined by OPTION...\n\n"
		<< "Options are ALL, MAT and VEC\n"
		<< "For all tests, matrix tests and vector tests respectively"
		<< std::endl;
	return 0;
}

int	main(int ac, char **av)
{
	if (ac > 2 || (ac == 2 && std::strcmp(av[1], "HELP") == 0))
		return usage();

	uint8_t	option = OPTION_ALL;
	if (ac == 2 && std::strcmp(av[1], "ALL") != 0)
	{
		if (std::strcmp(av[1], "MAT") == 0)
			option = OPTION_MAT;
		else if (std::strcmp(av[1], "VEC") == 0)
			option = OPTION_VEC;
		else
			return usage();
	}

	if (option == OPTION_ALL || option == OPTION_MAT)
	{
		try { testMatrices(); }
		catch (...)
		{
			std::cout << "An error occurred while testing matrices" << std::endl;
			return 1;
		}
	}

	if (option == OPTION_ALL || option == OPTION_VEC)
	{
		try { testVectors(); }
		catch (...)
		{
			std::cout << "An error occurred while testing vectors" << std::endl;
			return 2;
		}
	}

	return 0;
}
