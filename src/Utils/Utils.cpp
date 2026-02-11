/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:40:17 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/11 18:04:43 by frbranda         ###   ########.fr       */
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

void Print::Error(const std::string &str)
{
	std::cerr << BOLD_R << "[ERROR]" << RST
			  << str << ": " 
			  << BOLD_Y << strerror(errno) << RST
	<< std::endl;
}