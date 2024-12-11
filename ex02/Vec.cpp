/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:45:25 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/11 17:58:32 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	PmergeMe::printVec(size_t maxSize)
{
	size_t i = 0;
	while (i < maxSize && i < _vec.size())
	{
		std::cout << _vec[i];
		if (i + 1 < _vec.size())
			std::cout << " ";
		i++;
	}
	if (i < _vec.size())
		std::cout << "[...]";
	std::cout << std::endl;
}

void	PmergeMe::formAscendingPairs()
{
	int odd = _vec.size() % 2;
	for (size_t i = 0; i < _vec.size() - odd; i += 2)
	{
		if (_vec[i] > _vec[i + 1])
			_vecOfPair.push_back(pair(_vec[i + 1], _vec[i]));
		else
			_vecOfPair.push_back(pair(_vec[i], _vec[i + 1]));
	}
}

vecPair	PmergeMe::sortAscendingPairs(vecPair vecOfPair)
{
	uint	mid = vecOfPair.size() / 2;
	vecPair	left(vecOfPair.begin(), vecOfPair.begin() + mid);
	vecPair	right(vecOfPair.begin() + mid, vecOfPair.end());
	if (vecOfPair.size() == 1)
		return vecOfPair;

	left = sortAscendingPairs(left);
	right = sortAscendingPairs(right);
	uint	i = 0; // index to iterate through pairs vector "left"
	uint	j = 0; // index to iterate through pairs vector "right"
	uint	k = 0; // index of the sorted pairs vector
	while (i < left.size() && j < right.size())
	{
		if (left[i].second < right[j].second)
		{
			vecOfPair[k] = left[i];
			i++;
		}
		else
		{
			vecOfPair[k] = right[j];
			j++;
		}
		k++;
	}
	/* if some pairs left alone in one side, put them into sorted vector */
	while (i < left.size())
	{
		vecOfPair[k] = left[i];
		i++;
		k++;
	}
	while (j < right.size())
	{
		vecOfPair[k] = right[j];
		j++;
		k++;
	}
	return vecOfPair;
}

void	PmergeMe::insertFirstBatchOfNum()
{
	/* insert the larger of each pair (sorted asc pair) into new vector */
	size_t	size = _vec.size();
	if (_vec.size() % 2 == 1)
		_lastVecElement = _vec.back();
	_vec.clear();
	_vec.reserve(size);
	_vec.push_back(_vecOfPair.begin()->first);
	_vec.push_back(_vecOfPair.begin()->second);
	for (size_t i = 1; i < _vecOfPair.size(); i++)
		_vec.push_back(_vecOfPair[i].second);
}

void	PmergeMe::insertRestOfNum()
{
	uint	jacobsthalDistance[] = {2, 2, 6, 10, 26, 42, 106, 170, 426, 682, 1706, 2730, 6826, 10922, 27306, 43690, 109226, 174762, 436906, 699050};
	uint	iStart = 1;
	uint	iEnd = 0;
	/* iterate through the distance suite and insert pending num by group */
	for (uint i = 0; i < sizeof(jacobsthalDistance) / sizeof(uint); i++)
	{
		uint distance = jacobsthalDistance[i];
		iEnd = iStart + distance;
		if (iEnd > _vecOfPair.size())
			iEnd = _vecOfPair.size();
		while (--iEnd >= iStart)
		{
			/* find the position of target num's paired num */
			vec::iterator it = std::find(_vec.begin(), _vec.end(), _vecOfPair[iEnd].second);
			insertNumWithBinarySearch(_vecOfPair[iEnd].first, it - _vec.begin() - 1);
		}
		iStart += distance;
		if (_vec.size() == _vecOfPair.size() * 2)
			break;
	}
	if (_lastVecElement)
		insertNumWithBinarySearch(_lastVecElement, _vec.size() - 1);
}

void	PmergeMe::insertNumWithBinarySearch(uint num, uint iMax)
{
	// std::cout << "inserting " << num << " from position 0 to " << iMax << std::endl;
	// printVec(iMax + 1);
 	uint	low = 0, high = iMax; // high index is inclusive
	while (low < high)
	{
		uint mid = low + (high - low) / 2;
		// std::cout << "low:" << low << ", high:" << high << ", mid:" << mid << std::endl;
		if (num < _vec[mid])
		{
			if (mid == 0)
				high = 0;
			else
				high = mid - 1;
		}
		else
			low = mid + 1;
	}
	if (num < _vec[low])
		_vec.insert(_vec.begin() + low, num);
	else
		_vec.insert(_vec.begin() + low + 1, num);
}

void	PmergeMe::sortVec()
{
	formAscendingPairs();
	_vecOfPair = sortAscendingPairs(_vecOfPair);
	// print vector of pair
	// for (size_t i = 0; i < _vecOfPair.size() && i < MAX_PRINT; i++)
	// 	std::cout << "[" << _vecOfPair[i].first << " " << _vecOfPair[i].second << "] ";
	// std::cout << std::endl;
	insertFirstBatchOfNum();
	insertRestOfNum();
}
