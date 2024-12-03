/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:54:04 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/03 19:02:14 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& src)
{
	*this = src;
}

PmergeMe::PmergeMe(vec sequence)
{
	_vec = sequence;
	_last = -1;
	_vecOfPair.reserve(sequence.size() / 2);
	_lst = lst(sequence.begin(), sequence.end());
}

PmergeMe::~PmergeMe()
{
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& rhs)
{
	if (this != &rhs)
	{
		_vec = rhs._vec;
		_vecOfPair = rhs._vecOfPair;
		_lst = rhs._lst;
		_lstOfPair = rhs._lstOfPair;
	}
	return *this;
}

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
	// print vector of pair
	for (size_t i = 0; i < _vecOfPair.size(); i++)
		std::cout << "[" << _vecOfPair[i].first << " " << _vecOfPair[i].second << "] ";
	std::cout << std::endl;
}

vecPair	PmergeMe::sortAscendingPairsVec(vecPair vecOfPair)
{
	uint	mid = vecOfPair.size() / 2;
	vecPair	left(vecOfPair.begin(), vecOfPair.begin() + mid);
	vecPair	right(vecOfPair.begin() + mid, vecOfPair.end());
	if (vecOfPair.size() == 1)
		return vecOfPair;

	left = sortAscendingPairsVec(left);
	right = sortAscendingPairsVec(right);
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
		_last = _vec.back();
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
			/* find the idx of target num's paired num */
			vec::iterator it = std::find(_vec.begin(), _vec.end(), _vecOfPair[iEnd].second);
			insertNumWithBinarySearch(_vecOfPair[iEnd].first, it - _vec.begin() - 1);
		}
		iStart += distance;
		if (_vec.size() == _vecOfPair.size() * 2)
			break;
	}
	if (_last != -1)
		insertNumWithBinarySearch(static_cast<uint>(_last), _vec.size() - 1);
}

void	PmergeMe::insertNumWithBinarySearch(uint num, uint iMax)
{
	std::cout << "inserting " << num << " from 0 to " << iMax << std::endl;
	printVec(iMax + 1);
 	uint	low = 0, high = iMax; // high index is inclusive
	while (low < high)
	{
		uint mid = low + (high - low) / 2;
		if (num < _vec[mid])
			high = mid - 1;
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
	_vecOfPair = sortAscendingPairsVec(_vecOfPair);
	// print vector of pair
	for (size_t i = 0; i < _vecOfPair.size(); i++)
		std::cout << "[" << _vecOfPair[i].first << " " << _vecOfPair[i].second << "] ";
	std::cout << std::endl;
	insertFirstBatchOfNum();
	insertRestOfNum();
}

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

void	PmergeMe::sortLst()
{

}

vec		PmergeMe::getVec() const
{
	return _vec;
}

lst		PmergeMe::getLst() const
{
	return _lst;
}
