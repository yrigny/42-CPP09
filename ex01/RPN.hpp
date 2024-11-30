/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:39:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/30 12:19:15 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <string>
# include <deque>
# include <sstream>
# include <cstdlib>

class RPN
{
	private:

		std::string 	_expression;
		std::deque<int>	_deque;

	public:

		RPN();
		RPN(std::string expression);
		RPN(const RPN &rpn);
		~RPN();

		RPN&	operator=(const RPN &rpn);
		void	calculate();
		void	operateFrontElements(char operation);
		void	operateBackElements(char operation);
		
		class	DividedByZeroException : std::exception
		{
			const char*	what() const throw();
		};
};

#endif
