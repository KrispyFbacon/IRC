/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:37:03 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/25 14:19:55 by frbranda         ###   ########.fr       */
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
		~Client() {};


		//  ── Buffer Handler ──
		// Getters
		// std::string& getBuffer();
		// size_t getBufferSize() const;
		
		// Helpers
		// void appendBuffer(const char* data, ssize_t len);
		// bool getNextMessage(std::string& msg);
		// void clearBuffer();

		int	getFd() const
		{
			return _fd;
		}
		
		std::string& getBuffer()
		{
			return _buffer;
		}
		
		size_t getBufferSize() const
		{
			return _buffer.size();
		};
		
		void appendBuffer(const char* data, ssize_t len)
		{
			_buffer.append(data, len);
		};

		bool getNextMessage(std::string& msg)
		{
			size_t pos = _buffer.find("\r\n");
			if (pos == std::string::npos)
				return false;
			msg = _buffer.substr(0, pos);
			_buffer.erase(0, pos + 2);
			return true;
		};

		void clearBuffer()
		{
			std::string().swap(_buffer);
		};
	
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
			void setNonBlocking(int fd);
			void epollCreate (int flags);
			void epollAdd (int fd, uint32_t events);
			void epollMod (int fd, uint32_t events);
			void epollDel (int fd);

		// TODO Event handlers
			void handleNewConnection();
			void handleClientMessage(int clientFd);
			void removeClient(int clientFd);


		// TODO IRC logic (Parsing)
			// void processMessage(int fd, const std::string& msg);
		
	public:
		Server(int port);
		~Server();

		void initServer();
		void run();
		void cleanup();

		// TODO CLient management
		Client* getClient(int clientFd);
		// TODO Channel management
};

#endif