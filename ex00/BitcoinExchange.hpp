/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:37:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/11/28 22:50:08 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <fstream>
# include <map>
# include <string>
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

		class NoDatabaseException : std::exception
		{
			const char*	what() const throw();
		};
};

#endif
