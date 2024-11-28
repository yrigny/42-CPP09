/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:39:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/28 21:51:47 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP
# include <string>
# include <stack>

class RPN
{
	private:
		std::string _expression;

	public:
		RPN();
		RPN(std::string expression);
		RPN(const RPN &rpn);
		~RPN();

		RPN &operator=(const RPN &rpn);
		void calculate();
};

#endif
