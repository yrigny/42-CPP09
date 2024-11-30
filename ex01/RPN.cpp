/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:44:08 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/30 12:03:49 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _expression("")
{
}

RPN::RPN(std::string expression) : _expression(expression)
{
}

RPN::RPN(const RPN& src)
{
	*this = src;
}

RPN::~RPN()
{
}

RPN&	RPN::operator=(const RPN& rhs)
{
	if (this != &rhs)
	{
		_expression = rhs._expression;
		_deque = rhs._deque;
	}
	return *this;
}

void	RPN::calculate()
{
	std::stringstream	ss(_expression);
	int		num;
	char	chr;

	while (ss >> chr)
	{
		if (strchr("0123456789", chr))
		{
			num = chr - '0';
			_deque.push_back(num);
		}
		else if (strchr("+-*/", chr))
		{
			if (_deque.size() == 2)
				operateFrontElements(chr);
			else if (_deque.size() > 2)
				operateBackElements(chr);
		}
	}
	if (_deque.size() == 1)
		std::cout << _deque.front() << std::endl;
	else
		std::cout << "Error" << std::endl;
}

void	RPN::operateFrontElements(char operation)
{
	int num1 = _deque.front();
	_deque.pop_front();
	if (operation == '+')
		_deque.front() += num1;
	else if (operation == '-')
		_deque.front() = num1 - _deque.front();
	else if (operation == '*')
		_deque.front() *= num1;
	else if (operation == '/' && _deque.front() == 0)
		throw DividedByZeroException();
	else
		_deque.front() = num1 / _deque.front();
}

void	RPN::operateBackElements(char operation)
{
	int	num2 = _deque.back();
	_deque.pop_back();
	if (operation == '+')
		_deque.back() += num2;
	else if (operation == '-')
		_deque.back() -= num2;
	else if (operation == '*')
		_deque.back() *= num2;
	else if (operation == '/' && num2 == 0)
		throw DividedByZeroException();
	else
		_deque.back() /= num2;
}

const char*	RPN::DividedByZeroException::what() const throw()
{
	return "Error: division by 0";
}
