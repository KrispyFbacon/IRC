/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:40:17 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/12 17:44:42 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"


void Print::StdOut(const std::string &str)
{
	std::cout << str << std::endl;
}

void Print::StdErr(const std::string &str)
{
	std::cerr << str << std::endl;
}


void Print::TimeStamp ()
{
	std::time_t t = std::time(NULL);
	std::tm *tm = std::localtime(&t);

	char buffer[9];
	std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);

	std::cout << TIMESTAMP
			<< "[" << buffer << "] "
			<< RST;
}

void Print::Debug (const std::string& str)
{
	if (DEBUG)
	{
		Print::TimeStamp();
		Print::StdOut( " " + str);
	}
}


/* ================================ Status ================================= */

void Print::Ok (const std::string& str)
{
	std::cout << BOLD_G << "[ OK ] " << RST
			  << str
	<< std::endl;
}

void Print::Error(const std::string &str)
{
	std::cerr << BOLD_R << "[ ERROR ] " << RST
			  << str << ": " 
			  << NUM_COLOR << strerror(errno) << RST
	<< std::endl;
}

void Print::Fail(const std::string &str)
{
	std::cerr << BOLD_R << "[ FAIL ] " << RST
			  << str << ": " 
			  << NUM_COLOR << strerror(errno) << RST
	<< std::endl;
}