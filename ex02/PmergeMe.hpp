/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:53:01 by yrigny            #+#    #+#             */
/*   Updated: 2024/12/11 18:00:19 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <list>
# include <vector>
# include <algorithm>
# define MAX_PRINT 10

typedef unsigned int			uint;
typedef std::pair<uint, uint>	pair;
typedef std::vector<uint>		vec;
typedef std::vector<pair>		vecPair;
typedef std::list<uint>			lst;
typedef std::list<pair>			lstPair;
typedef lst::iterator			lstIt;
typedef lstPair::iterator		lstPairIt;

class PmergeMe
{
	private:
	
		vec		_vec;
		uint	_lastVecElement;
		vecPair	_vecOfPair;

		void	formAscendingPairs();
		vecPair	sortAscendingPairs(vecPair vecOfPair);
		void	insertFirstBatchOfNum();
		void	insertRestOfNum();
		void	insertNumWithBinarySearch(uint num, uint iMax);

		lst		_lst;
		uint	_lastLstElement;
		lstPair	_lstOfPair;

		void	formAscendingPairsLst();
		lstPair	sortAscendingPairsLst(lstPair lstOfPair);
		void	insertFirstBatchOfNumToLst();
		void	insertRestOfNumToLst();
		void	insertNumToLstWithBinarySearch(uint num, uint iMax);

	public:

		PmergeMe();
		PmergeMe(vec sequence);
		PmergeMe(const PmergeMe& src);
		~PmergeMe();
		PmergeMe&	operator=(const PmergeMe& rhs);
		void		sortVec();
		void		sortLst();
		const vec&	getVec();
		const lst&	getLst();
		void		printVec(size_t maxSize);
		void		printLst(size_t maxSize);
};

#endif
