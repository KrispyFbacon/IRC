/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:27:40 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/10 17:58:41 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sys/socket.h> // socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h> // htons(), htonl(), ntohs(), ntohl(), INADDR_ANY (IPv4)
#include <arpa/inet.h> // inet_addr(), inet_ntoa(), inet_ntop()
#include <unistd.h> // close(), read(), write()
#include <cstring> // std::memset(), std::strlen(), std::strcmp()
#include <errno.h>

#include "Color.hpp"


#define PORT 8080

//https://www.tutorialspoint.com/cplusplus/cpp_socket_programming.html


void printError(const std::string &msg)
{
	std::cerr << BOLD_R << msg << ": " << BOLD_Y << strerror(errno) << RST << std::endl;
}

#endif