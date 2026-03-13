/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:37:03 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/26 14:11:25 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Parsing.hpp"
#include "CommandFactory.hpp"

class Client;
class Channel;
//class CommandFactory;

class Server
{
	private:
		typedef std::map<int, Client*>::iterator clientIt;
		typedef std::map<std::string, Channel*>::iterator channelIt;

		// Socket _serverSocked(); TODO maybe since server and clients will have their own socket
		int _fd; // serverFd
		int _epfd; // epoll Fd
		std::string _port; //TODO turn into const
		std::string _password;
		
		std::map<int, Client*> _clients;
		std::map<std::string, Channel*> _channels;
		CommandFactory _cmdFactory;

		// ── I/O helpers ──
		void createAndBindSocket();
		void setNonBlocking(int fd);
		void epollCreate (int flags);
		void epollAdd (int fd, uint32_t events);
		void epollMod (int fd, uint32_t events);
		void epollDel (int fd);

		// ── Event handlers ──
		void handleNewConnection();
		void handleClientMessage(int clientFd);
		void removeClient(int clientFd);


		// TODO IRC logic (Parsing)
			// void processMessage(int fd, const std::string& msg);
		
	public:
		Server(const std::string& port, const std::string& password);
		~Server();

		void initServer();
		void run();
		void cleanup();

		// Getters
		std::string getPassword() const; // TODO inline?

		// TODO CLient management
		Client* getClient(int clientFd);
		Client* getClientByNickname(const std::string& nickname);
		// TODO Channel management
		Channel* getChannel(std::string channelName);
};

#endif