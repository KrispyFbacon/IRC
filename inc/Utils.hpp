/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:27:40 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/17 15:34:06 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>			// Storing Clients (fd -> Client)
#include <algorithm>	// std::find

// --- C++ Standard Tools (Allowed) ---
#include <ctime> 		// time_t
#include <iomanip>
#include <sstream>
#include <fstream>

// --- Network / Socket Core ---
#include <sys/socket.h>	// socket, setsockopt, getsockname, bind, connect, listen, accept, send, recv
#include <netinet/in.h>	// htons, htonl, ntohs, ntohl, INADDR_ANY (IPv4)
#include <arpa/inet.h> 	// inet_addr, inet_ntoa, inet_ntop
#include <netdb.h> 		// getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo

// --- I/O & File Control ---
#include <unistd.h> 	// close, lseek, (read, write - implied)
#include <fcntl.h> 		// fcntl(), O_NONBLOCK (used for non-blocking I/O)
#include <sys/stat.h> 	// fstat
#include <poll.h> 		// poll

// --- Signal Handling ---
#include <signal.h>		// signal, sigaction, sigemptyset, sigfillset, sigaddset, sigdelset, sigismember

// --- Utilities ---
#include <cstring>		// std::memset, std::strlen, std::strcmp
#include <errno.h>		// errno

#include "Color.hpp"

//https://www.tutorialspoint.com/cplusplus/cpp_socket_programming.html



/* ========================== Defines =========================== */

// --- Debug ---
#ifndef DEBUG
	#define DEBUG 1
#endif

// --- Network / Socket Core ---
#define PORT 6667
#define BUFFER_SIZE 1024
#define MAX_EVENTS 64 // 128 (64: clean & efficent, 128: very safe but more resource intensive)

// --- Colors ---
#define NUM_COLOR	RGB_BOLD(255, 165, 0)
#define TIMESTAMP	BOLD_Y



/* ========================== Variables and Constants =========================== */

// --- Global Variables ---
extern bool g_running;


// --- Utility Classes ---
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


// --- Template Functions ---
template <typename T>
std::string toString(T src)
{
	std::stringstream ss;
	ss << src;
	return ss.str();
}

#endif