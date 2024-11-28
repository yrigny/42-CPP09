/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:37:25 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/28 23:07:26 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::ifstream	database("data.csv");
	if (!database.is_open())
		throw NoDatabaseException();
	std::string	line;
	getline(database, line);
	if (line != "date,exchange_rate")
		throw NoDatabaseException();
	while (getline(database, line))
	{
		// substr (0, find(,)) -> date

		// substr (find(,) + 1) -> rate

		// add to map

	}
	database.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	if (this != &rhs)
	{
		_exchangeRate = rhs._exchangeRate;
	}
	return *this;
}

void	BitcoinExchange::calculateValue(std::string inputLine)
{
	// parse input date and amount

	// find exchange rate for date

	// calculate value
}

const char*	BitcoinExchange::NoDatabaseException::what() const throw()
{
	return "Error: no database found.";
}
