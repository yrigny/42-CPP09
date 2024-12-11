/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:54:04 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/11 17:59:31 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(vec sequence)
{
	_vec = sequence;
	_lastVecElement = 0;
	_vecOfPair.reserve(sequence.size() / 2);
	_lst = lst(sequence.begin(), sequence.end());
	_lastLstElement = 0;
}

PmergeMe::PmergeMe(const PmergeMe& src)
{
	*this = src;
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

const vec&	PmergeMe::getVec()
{
	return _vec;
}

const lst&	PmergeMe::getLst()
{
	return _lst;
}
