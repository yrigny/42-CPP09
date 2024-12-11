/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lst.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:46:58 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/11 17:55:24 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	PmergeMe::printLst(size_t maxSize)
{
	size_t	i = 0;
	lstIt	it = _lst.begin();
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

static lstPairIt	locate(lstPair& lst, uint index)
{
	if (index >= lst.size())
		return lst.end();
	lstPairIt it;
	if (index < lst.size() / 2)
	{
		it = lst.begin();
		while (index--)
			it++;
	}
	else
	{
		it = lst.end();
		while (index++ < lst.size())
			it--;
	}
	return it;
}

static lstIt	locate(lst& lst, uint index)
{
	if (index >= lst.size())
		return lst.end();
	lstIt it;
	if (index < lst.size() / 2)
	{
		it = lst.begin();
		while (index--)
			it++;
	}
	else
	{
		it = lst.end();
		while (index++ < lst.size())
			it--;
	}
	return it;
}

uint	dist(lstIt subtracted, lstIt subtractor)
{
	uint dist = 0;
	while (subtracted != subtractor)
	{
		dist++;
		subtracted--;
	}
	return dist;	
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
	uint		mid = lstOfPair.size() / 2 + lstOfPair.size() % 2;
	lstPairIt	midIt = locate(lstOfPair, mid);
	lstPair		left(lstOfPair.begin(), midIt);
	lstPair		right(midIt, lstOfPair.end());
	
	if (lstOfPair.size() == 1)
		return lstOfPair;
	
	left = sortAscendingPairsLst(left);
	right = sortAscendingPairsLst(right);
	uint	i = 0; // index to iterate through pairs list "left"
	uint	j = 0; // index to iterate through pairs list "right"
	uint	k = 0; // index of the sorted pairs list
	while (i < left.size() && j < right.size())
	{
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

void	PmergeMe::insertFirstBatchOfNumToLst()
{
	if (_lst.size() % 2 == 1)
		_lastLstElement = _lst.back();
	_lst.clear();
	_lst.push_back(_lstOfPair.begin()->first);
	_lst.push_back(_lstOfPair.begin()->second);
	lstPairIt it = _lstOfPair.begin();
	while (++it != _lstOfPair.end())
		_lst.push_back(it->second);
}

void	PmergeMe::insertRestOfNumToLst()
{
	uint	jacobsthalDistance[] = {2, 2, 6, 10, 26, 42, 106, 170, 426, 682, 1706, 2730, 6826, 10922, 27306, 43690, 109226, 174762, 436906, 699050};
	uint	iStart = 1;
	uint	iEnd = 0;
	for (uint i = 0; i < sizeof(jacobsthalDistance) / sizeof(uint); i++)
	{
		uint distance = jacobsthalDistance[i];
		iEnd = iStart + distance;
		if (iEnd > _lstOfPair.size())
			iEnd = _lstOfPair.size();
		while (--iEnd >= iStart)
		{
			lstIt it = std::find(_lst.begin(), _lst.end(), locate(_lstOfPair, iEnd)->second);
			insertNumToLstWithBinarySearch(locate(_lstOfPair, iEnd)->first, dist(it, _lst.begin()) - 1);
		}
		iStart += distance;
		if (_lst.size() == _lstOfPair.size() * 2)
			break;
	}
	if (_lastLstElement)
		insertNumToLstWithBinarySearch(_lastLstElement, _lst.size() - 1);
}

void	PmergeMe::insertNumToLstWithBinarySearch(uint num, uint iMax)
{
 	uint	low = 0, high = iMax; // high index is inclusive
	while (low < high)
	{
		uint mid = low + (high - low) / 2;
		if (num < *locate(_lst, mid))
		{
			if (mid == 0)
				high = 0;
			else
				high = mid - 1;
		}
		else
			low = mid + 1;
	}
	if (num < *locate(_lst, low))
		_lst.insert(locate(_lst, low), num);
	else
		_lst.insert(locate(_lst, low + 1), num);
}

void	PmergeMe::sortLst()
{
	formAscendingPairsLst();
	_lstOfPair = sortAscendingPairsLst(_lstOfPair);
	// print lst of pair
	// for (lstPairIt it = _lstOfPair.begin(); it != _lstOfPair.end(); it++)
	// 	std::cout << "[" << it->first << " " << it->second << "] ";
	// std::cout << std::endl;
	insertFirstBatchOfNumToLst();
	insertRestOfNumToLst();
}
