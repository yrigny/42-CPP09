/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:44:27 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/30 13:57:08 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <stdexcept>
#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac == 2 && av[1] != NULL)
	{
		for (size_t i = 0; i < strlen(av[1]); i++)
		{
			if (!strchr("0123456789 +-*/", av[1][i]))
			{
				std::cout << "Error" << std::endl;
				return 0;
			}
		}
		std::string	str(av[1]);
		try
		{
			RPN	rpn(str);
			rpn.calculate();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	else
		std::cout << "Usage: ./RPN [expression]" << std::endl;
	return 0;
}
