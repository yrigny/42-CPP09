/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:53:01 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/30 17:17:25 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <list>
# include <vector>

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
		vec		_vec2;
		vecPair	_vecOfPair;
		lst		_lst;
		lst		_lst2;
		lstPair	_lstOfPair;

	public:
		PmergeMe();
		PmergeMe(vec sequence);
		PmergeMe(const PmergeMe& src);
		~PmergeMe();
		PmergeMe&	operator=(const PmergeMe& rhs);
		void		printVec(size_t maxSize);
		void		sortVec();
		void		sortPairVec();
		void		printLst(size_t maxSize);
		void		sortLst();
		vec			getVec() const;
		lst			getLst() const;
};

#endif
