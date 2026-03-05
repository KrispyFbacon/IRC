/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:27:40 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/26 14:09:28 by frbranda         ###   ########.fr       */
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
#include <sys/types.h> // socklen_t, ssize_t, pid_t
#include <netinet/in.h>	// htons, htonl, ntohs, ntohl, INADDR_ANY (IPv4)
#include <arpa/inet.h> 	// inet_addr, inet_ntoa, inet_ntop
#include <netdb.h> 		// getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo

// --- I/O & File Control ---
#include <unistd.h> 	// close, lseek, (read, write - implied)
#include <fcntl.h> 		// fcntl(), O_NONBLOCK (used for non-blocking I/O)
#include <sys/stat.h> 	// fstat
#include <sys/epoll.h> 	// epoll

// --- Signal Handling ---
#include <signal.h>		// signal, sigaction, sigemptyset, sigfillset, sigaddset, sigdelset, sigismember

// --- Utilities ---
#include <cstring>		// std::memset, std::strlen, std::strcmp
#include <errno.h>		// errno

#include "Exceptions.hpp"
#include "Color.hpp"

//https://www.tutorialspoint.com/cplusplus/cpp_socket_programming.html



/* ================================ Defines ================================ */

// --- Debug ---
#ifndef DEBUG
	#define DEBUG 1
#endif

// --- Network / Socket Core ---
#define PORT 6667
#define BACKLOG 10
#define BUFFER_SIZE 1024
#define MAX_MESSAGE_SIZE 4096
#define MAX_EVENTS 64 // 128 (64: clean & efficent, 128: very safe but more resource intensive)

// --- Colors ---
#define NUM_COLOR	RGB_BOLD(255, 165, 0)
#define TIMESTAMP	BOLD_Y



/* ======================== Variables and Constants ======================== */

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
		static void Warn (const std::string& str);
		
		
		static void InputError (const std::string& str);
};


// --- Template Functions ---
template <typename T>
std::string toString(T src)
{
	std::stringstream ss;
	ss << src;
	return ss.str();
}


// --- Args Validation ---
bool isValidPort(const std::string& port);
bool isValidPassword(const std::string& password);

// --- String Helper ---
std::string	getFirstString(const std::string);



// ERR_NOSUCHNICK = 401,
// ERR_NOSUCHCHANNEL = 403,
// ERR_UNKNOWNCOMMAND = 421,
// ERR_NONICKNAMEGIVEN = 431,
// ERR_USERNOTINCHANNEL = 441,
// ERR_NOTONCHANNEL = 442,
// ERR_USERONCHANNEL = 443,
// ERR_NOTREGISTERED = 451,
// ERR_NEEDMOREPARAMS = 461,
// ERR_ALREADYREGISTERED = 462,
// ERR_PASSWDMISMATCH = 464,
// ERR_CHANNELISFULL = 471,
// ERR_UNKNOWNMODE = 472,
// ERR_INVITEONLYCHAN = 473,
// ERR_BADCHANNELKEY = 475,
// ERR_CHANOPRIVSNEEDED = 482,
// ERR_INVALIDMODEPARAM = 696

#endif