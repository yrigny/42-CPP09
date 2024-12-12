/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:54:23 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/13 00:19:39 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <sstream>
#include <ctime>
#include "PmergeMe.hpp"
#define CLR "\e[32m"
#define NONE "\e[0m"

bool	isUint(std::string str)
{
	std::stringstream ss(str);
	int i;
	if (ss >> i && i > 0 && i <= INT_MAX)
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
	while (i < sequence.size() && sequence[i] != n)
		i++;
	if (i == sequence.size())
		return true;
	std::cout << "Error: " << str << " is not unique." << std::endl;
	return false;
}

bool	isSortedVec(const vec& vec)
{
    return std::adjacent_find(vec.begin(), vec.end(), std::greater<uint>()) == vec.end();
}

bool	isSortedLst(const lst& lst)
{
	return std::adjacent_find(lst.begin(), lst.end(), std::greater<uint>()) == lst.end();
}

void	sort(PmergeMe &pm)
{
	std::cout << CLR"Before:  " NONE;
	pm.printVec(MAX_PRINT);

	std::clock_t start, end;
	double durationUs;

	start = std::clock();
	pm.sortVec();
	end = std::clock();
	durationUs = end - start;

	std::cout << CLR "After:   " NONE;
	pm.printVec(MAX_PRINT);
	std::cout << CLR "Time to process a range of " << pm.getVec().size() << " elements with std::vector : " NONE;
	std::cout << durationUs << " us" << std::endl;

	start = std::clock();
	pm.sortLst();
	end = std::clock();
	durationUs = end - start;
	std::cout << CLR "Time to process a range of " << pm.getLst().size() << " elements with std::list   : " NONE;
	std::cout << durationUs << " us" << std::endl;

	std::cout << std::boolalpha;
	std::cout << "Vec is sorted: " << isSortedVec(pm.getVec()) << std::endl;
	std::cout << "Lst is sorted: " << isSortedLst(pm.getLst()) << std::endl;
	std::cout << std::noboolalpha;
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
