/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:54:23 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/30 16:03:05 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <sstream>
#include <ctime>
#include "PmergeMe.hpp"
#define MAX_PRINT 10

bool	isUint(std::string str)
{
	std::stringstream ss(str);
	uint i;
	if (ss >> i && i <= UINT_MAX)
		return true;
	std::cout << "Error: " << str << " is not an unsigned integer." << std::endl;
	return false;
}

bool	isUnique(std::string str, vec sequence)
{
	uint	n = std::atoi(str.c_str());
	size_t	i = 0;
	if (sequence.size() == 0)
		return true;
	while (i < sequence.size() && sequence[i++] != n)
		;
	if (i == sequence.size())
		return true;
	std::cout << "Error: " << str << " is not unique." << std::endl;
	return false;
}

void	sort(PmergeMe &pm)
{
	std::cout << "Before:  ";
	pm.printVec(MAX_PRINT);

	std::clock_t start, end;
	double durationUs;

	start = std::clock();
	pm.sortVec();
	end = std::clock();
	durationUs = 1e6 * (end - start) / (double) CLOCKS_PER_SEC;

	std::cout << "After:   ";
	pm.printVec(MAX_PRINT);
	
	std::cout << "Time to process a range of " << pm.getVec().size() << " elements with std::vector : ";
	std::cout << durationUs << " us" << std::endl;

	start = std::clock();
	pm.sortLst();
	end = std::clock();
	durationUs = 1e6 * (end - start) / (double) CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << pm.getLst().size() << " elements with std::list   : ";
	std::cout << durationUs << " us" << std::endl;
}

int main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "Usage: ./PmergeMe [number1] [number2] [number3] ..." << std::endl;
		return 0;
	}
	vec	sequence;
	int i = 0;
	while (av[++i])
	{
		if (!isUint(av[i]))
			return 1;
		if (!isUnique(av[i], sequence))
			return 1;
		sequence.push_back(std::atoi(av[i]));
	}
	PmergeMe pm(sequence);
	sort(pm);
	return 0;
}
