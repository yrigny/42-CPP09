/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lst.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:46:58 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/04 20:03:32 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


void	PmergeMe::printLst(size_t maxSize)
{
	size_t i = 0;
	lst::iterator it = _lst.begin();
	while (i < maxSize && it != _lst.end())
	{
		std::cout << *it;
		if (++it != _lst.end())
			std::cout << " ";
		i++;
	}
	if (it != _lst.end())
		std::cout << "[...]";
	std::cout << std::endl;
}

static void		move(lstIt& it, int n)
{
	if (n > 0)
		while (n--) it++;
	else
		while (n++) it--;
}

static lstIt	next(lstIt it)
{
	return ++it;
}

static lstPairIt	at(lstPair& lst, uint target)
{
	uint	lstSize = lst.size();
	lstPairIt	it;
	if (target > lstSize)
		it = lst.end();
	else if (target < lstSize / 2)
	{
		it = lst.begin();
		while (target--) it++;
	}
	else
	{
		it = lst.end();
		while (lstSize - target--) it--;
	}
	return it;
}

void	PmergeMe::formAscendingPairsLst()
{
	lstIt	end = _lst.end();
	if (_lst.size() % 2 == 1)
		end--;
	for (lstIt it = _lst.begin(); it != end; move(it, 2))
	{
		if (*it > *next(it))
			_lstOfPair.push_back(pair(*next(it), *it));
		else
			_lstOfPair.push_back(pair(*it, *next(it)));
	}
}

lstPair	PmergeMe::sortAscendingPairsLst(lstPair lstOfPair)
{
	
}

void	PmergeMe::sortLst()
{
	printLst(MAX_PRINT);
	formAscendingPairsLst();
	
	// print lst of pair
	for (lstPairIt it = _lstOfPair.begin(); it != _lstOfPair.end(); it++)
		std::cout << "[" << it->first << " " << it->second << "] ";
	std::cout << std::endl;

	_lstOfPair = sortAscendingPairsLst(_lstOfPair);
	// insertFirstBatchOfNum();
	// insertRestOfNum();
}