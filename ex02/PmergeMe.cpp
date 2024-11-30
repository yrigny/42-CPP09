/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:54:04 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/30 17:39:09 by yrigny           ###   ########.fr       */
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
		_vec2 = rhs._vec2;
		_vecOfPair = rhs._vecOfPair;
		_lst = rhs._lst;
		_lst2 = rhs._lst2;
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

void	PmergeMe::sortPairVec()
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
}

void	PmergeMe::sortVec()
{
	sortPairVec();
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
