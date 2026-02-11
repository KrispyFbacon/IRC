/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:27:40 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/11 18:00:20 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <sys/socket.h> // socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h> // htons(), htonl(), ntohs(), ntohl(), INADDR_ANY (IPv4)
#include <arpa/inet.h> // inet_addr(), inet_ntoa(), inet_ntop()
#include <unistd.h> // close(), read(), write()
#include <cstring> // std::memset(), std::strlen(), std::strcmp()
#include <errno.h>
#include <ctime> // time_t

#include "Color.hpp"

//https://www.tutorialspoint.com/cplusplus/cpp_socket_programming.html


#define PORT 8080

class Print
{
	public:
		static void StdOut (const std::string &str);
		static void StdErr(const std::string& str);
		static void Error (const std::string& str);
		
};

#endif