/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:37:03 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/19 18:45:09 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Utils.hpp"


// ── Per-client ──────────────────────────────────────────────────────────────
class Client
{
	private:
		int _fd;
	
		std::string _buffer;

	public:
		Client(int fd) : _fd(fd) {};
		~Client();

		
		void appendBuffer(const char* data, ssize_t len)
		{
			_buffer.append(data, len);
		}

		void getNextMessage(std::string& out)
		{
			
		}
	
};


// ── Server ──────────────────────────────────────────────────────────────────
class Server
{
	private:
		typedef std::map<int, Client*>::iterator clientIt;

		// Socket _serverSocked(); TODO maybe since server and clients will have their own socket
		int _fd; // serverFd
		int _epfd; // epoll Fd
		int _port;
		//std::string _password;
		
		std::map<int, Client*> _clients;
		//std::map<string, Channels*> _channels;

		// TODO I/O helpers
			bool setOption(int level, int optname, const void *optval, socklen_t optlen);
			bool setNonBlocking(int fd);
			bool epollCreate (int flags);
			bool epollAdd (int fd, uint32_t events);
			bool epollMod (int fd, uint32_t events);
			bool epollDel (int fd);

		// TODO Event handlers
			void handleNewConnection();
			void handleClientMessage(int clientFd);
			void removeClient(int clientFd);


		// TODO IRC logic (Parsing)
			// void processMessage(int fd, const std::string& msg);
		
	public:
		Server(int port);
		~Server();

		bool initServer();
		void run();
		void cleanup();

		// TODO CLient management
		Client* getClient(int clientFd);
		// TODO Channel management
};

#endif