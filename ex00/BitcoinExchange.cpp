/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:37:25 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/29 20:01:49 by yrigny           ###   ########.fr       */
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
		size_t	pos = line.find(',');
		if (pos == std::string::npos)
			throw NoDatabaseException();
		std::string	date = line.substr(0, pos);
		std::string	price = line.substr(pos + 1);
		std::cout << date << "," << price << std::endl;
		double	priceInDouble = strtod(price.c_str(), NULL);
		_exchangeRate[date] = priceInDouble;
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
	std::string	date;
	double		amount;
	double		price;

	/* check bad input */
	if (inputLine.length() < 14 || inputLine.find(" | ") == std::string::npos)
	{
		std::cout << "Error: bad input => " << inputLine << std::endl;
		return;
	}
	/* parse input date and amount */
	if (inputLine.length() >= 14)
	{
		date = inputLine.substr(0, 10);
		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			return;
		}
		amount = strtod(inputLine.substr(13).c_str(), NULL);
		if (amount <= 0)
		{
			std::cout << "Error: bad input => " << amount << std::endl;
			return;
		}
	}
	// find exchange rate for date
	price = _exchangeRate.at(date);
	// calculate value
}

bool	BitcoinExchange::isValidDate(std::string)
{
	
}

const char*	BitcoinExchange::NoDatabaseException::what() const throw()
{
	return "Error: no database found.";
}
