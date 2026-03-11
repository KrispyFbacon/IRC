/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:40:17 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/24 13:00:19 by frbranda         ###   ########.fr       */
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

void Print::Warn(const std::string &str)
{
	std::cerr << BOLD_Y << "[ FAIL ] " << RST << str
	<< std::endl;
}


void Print::InputError(const std::string& str)
{
	std::cerr << BOLD_R << "[ ERROR ] " << RST << str << "\n" << std::endl;
	std::cerr << BOLD_Y << "USAGE:" 
			  << RST << " ./ircserv <port 1-65535> <password>"
	<< std::endl;
}

/* ============================ Args Validation ============================ */

bool isValidPort(const std::string& port)
{
	if (port.empty())
		return false;
	
	for (std::string::size_type i = 0; i < port.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(port[i])))
			return false;
	}

	long n = std::strtol(port.c_str(), NULL, 10);
	return (n >= 1 && n <= 65535);
}

bool isValidPassword(const std::string& password)
{
	if (password.empty())
		return false;

	for (std::string::size_type i = 0; i < password.size(); ++i)
	{
		if (std::isspace(static_cast<unsigned char>(password[i])))
			return false;
		if (!std::isprint(static_cast<unsigned char>(password[i])))
			return false;
	}
	return true;
}

// bool isValidPort(const char* port)
// {
// 	if (!port || !(*port))
// 		return false;
	
// 	for (int i = 0; port[i] != '\0'; ++i)
// 	{
// 		if (!std::isdigit(static_cast<unsigned char>(port[i])))
// 			return false;
// 	}

// 	long n = std::strtol(port, NULL, 10);
// 	return (n >= 1 && n <= 65535);
// }

//
// bool isValidPassword(const char* password)
// {
// 	if (!password || !(*password))
// 		return false;

// 	for (int i = 0; password[i] != '\0'; ++i)
// 	{
// 		if (std::isspace(static_cast<unsigned char>(password[i])))
// 			return false;
// 		if (!std::isprint(static_cast<unsigned char>(password[i])))
// 			return false;
// 	}
// 	return true;
// }


/* ============================= String Helper ============================= */

std::string	getFirstString(const std::string str)
{
	size_t	pos = str.find_first_of(" ");
	std::string	firstString = str.substr(0, pos);

	return (firstString);
}

std::string	toUpper(const std::string &str)
{
	std::string	result = str;

	for (std::string::size_type i = 0; i < result.length(); i++)
		result[i] = std::toupper(static_cast<unsigned char>(result[i]));

	return (result);
}
