/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:37:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/30 13:57:43 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <fstream>
# include <map>
# include <iostream>
# include <cstdlib>
# include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_exchangeRate;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& src);
		~BitcoinExchange();
		
		BitcoinExchange&	operator=(const BitcoinExchange& rhs);
		void				calculateValue(std::string inputLine);
		bool				isValidDate(std::string date);

		class NoDatabaseException : public std::exception
		{
			const char*	what() const throw();
		};
};

#endif
