/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:53:01 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/04 14:33:02 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <list>
# include <vector>
# include <algorithm>
# define MAX_PRINT 15

typedef unsigned int			uint;
typedef std::pair<uint, uint>	pair;
typedef std::vector<uint>		vec;
typedef std::list<uint>			lst;
typedef std::vector<pair>		vecPair;
typedef std::list<pair>			lstPair;

class PmergeMe
{
	private:
	
		vec		_vec;
		int		_last;
		vecPair	_vecOfPair;

		void	formAscendingPairs();
		vecPair	sortAscendingPairsVec(vecPair vecOfPair);
		void	insertFirstBatchOfNum();
		void	insertRestOfNum();
		void	insertNumWithBinarySearch(uint num, uint iMax);

		lst		_lst;
		lstPair	_lstOfPair;

	public:

		PmergeMe();
		PmergeMe(vec sequence);
		PmergeMe(const PmergeMe& src);
		~PmergeMe();
		PmergeMe&	operator=(const PmergeMe& rhs);

		void	sortVec();
		void	sortLst();
		void	printVec(size_t maxSize);
		void	printLst(size_t maxSize);
		const vec&	getVec();
		const lst&	getLst();
};

#endif
