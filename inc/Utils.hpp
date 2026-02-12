/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:27:40 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/12 18:19:42 by frbranda         ###   ########.fr       */
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
#include <iomanip>
#include <sstream>
#include <fstream>
#include <signal.h>
#include <fcntl.h>

#include "Color.hpp"

//https://www.tutorialspoint.com/cplusplus/cpp_socket_programming.html


#ifndef DEBUG
	#define DEBUG 1
#endif


// Options:
#define PORT 6667
#define BUFFER_SIZE 1024


// Colors
#define NUM_COLOR	RGB_BOLD(255, 165, 0)
#define TIMESTAMP	BOLD_Y

// Global
extern bool g_running;

class Print
{
	public:
		static void StdOut (const std::string &str);
		static void StdErr(const std::string& str);
		
		static void TimeStamp ();
		
		static void Debug (const std::string& str);
		
		static void Ok (const std::string& str);
		static void Error (const std::string& str);
		static void Fail (const std::string& str);
		
};

template <typename T>
std::string toString(T src)
{
	std::stringstream ss;
	ss << src;
	return ss.str();
}

#endif