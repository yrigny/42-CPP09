/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lst.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:46:58 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/05 19:58:27 by yrigny           ###   ########.fr       */
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

static lstPairIt	locate(lstPair& lst, uint target)
{
	lstPairIt	it;
	
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
	uint	mid = lstOfPair.size() / 2 + lstOfPair.size() % 2;
	lstPair	left(lstOfPair.begin(), locate(lstOfPair, mid));
	lstPair	right(locate(lstOfPair, mid), lstOfPair.end());
	// print left lst of pair
	for (lstPairIt it = left.begin(); it != left.end(); it++)
		std::cout << "[" << it->first << " " << it->second << "] ";
	std::cout << std::endl;
	// print right lst of pair
	for (lstPairIt it = right.begin(); it != right.end(); it++)
		std::cout << "[" << it->first << " " << it->second << "] ";
	std::cout << std::endl;
	
	if (lstOfPair.size() == 1)
		return lstOfPair;
	
	left = sortAscendingPairsLst(left);
	right = sortAscendingPairsLst(right);
	uint	i = 0; // index to iterate through pairs list "left"
	uint	j = 0; // index to iterate through pairs list "right"
	uint	k = 0; // index of the sorted pairs list
	while (i < left.size() && j < right.size())
	{
		std::cout << "i = " << i << ", j = " << j << std::endl;
		uint	a = locate(left, i)->second;
		uint	b = locate(right,j)->second;
		if (a < b)
		{
			*locate(lstOfPair, k) = *locate(left, i);
			i++;
		}
		else
		{
			*locate(lstOfPair, k) = *locate(right, j);
			j++;
		}
		k++;
	}
	while (i < left.size())
	{
		*locate(lstOfPair, k) = *locate(left, i);
		i++;
		k++;
	}
	while (j < right.size())
	{
		*locate(lstOfPair, k) = *locate(right, j);
		j++;
		k++;
	}
	return lstOfPair;
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
	// print lst of pair
	for (lstPairIt it = _lstOfPair.begin(); it != _lstOfPair.end(); it++)
		std::cout << "[" << it->first << " " << it->second << "] ";
	std::cout << std::endl;
	
	// insertFirstBatchOfNum();
	// insertRestOfNum();
}