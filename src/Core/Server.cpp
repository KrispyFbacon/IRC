/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:35:52 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/11 18:21:43 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port) : _fd(-1), _port(port) {}

Server::~Server() {}

bool Server::initServer()
{
	// Step 1: Create socket
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
	{
		Print::Error("Failed to create socket");
		return false;
	}

	int opt = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) 
	{
		Print::Error("setsockopt() failed");
		return false;
	}

	// Step 2: Bind socket to address and port
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(_port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
	{
		Print::Error("Bind() failed");
		return false;
	}

	// Step 3: Start listening
	int backlog = 10;
	if (listen(_fd, backlog) < 0)
	{
		Print::Error("Lsiten() failed");
		return false;
	}

	std::cout << "Server Port: " << _port << std::endl;

	return true;
}