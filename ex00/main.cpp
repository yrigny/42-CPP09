/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:35:27 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/29 18:09:36 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		std::ifstream	file(av[1]);
		if (!file.is_open())
			std::cerr << "Error: could not open file." << std::endl;
		else
		{
			try
			{
				BitcoinExchange btc;
				std::string		line;
				getline(file, line);
				while (getline(file, line))
					btc.calculateValue(line);
				file.close();
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}
	else
		std::cout << "Usage: ./btc [input_database]" << std::endl;
	return 0;
}
