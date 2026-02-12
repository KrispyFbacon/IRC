/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:35:52 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/12 18:21:11 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port) : _fd(-1), _port(port) {}

Server::~Server()
{
	cleanup();
}

bool Server::initServer()
{
	// Step 1: Create socket
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
	{
		Print::Error("Failed to create socket");
		return false;
	}

	// Set socket to non-blocking
	// if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
	// {
	// 	Print::Error("fcntl() failed");
	// 	return false;
	// }

	int opt = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) 
	{
		Print::Error("setsockopt() failed");
		return false;
	}

	// Step 2: Bind socket to address and port
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(_port);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		Print::Error("Bind() failed");
		return false;
	}

	// Step 3: Start listening
	int backlog = 10;
	if (listen(_fd, backlog) < 0)
	{
		Print::Error("Listen() failed");
		return false;
	}

	std::cout << "Server Port: " << _port << std::endl;

	return true;
}


void Server::run()
{
	Print::Debug("Server running. Press Ctrl+C to stop.");

	while (g_running)
	{
		// Step 4: Accept incoming connection
		struct sockaddr_in clientAdress;
		socklen_t clientLen = sizeof(clientAdress);

		std::cout << "G_Running = " << (g_running ? "true" : "false") << std::endl;
		int clientFd = accept(_fd, (struct sockaddr*)&clientAdress, &clientLen);
		std::cout << "G_Running = " << (g_running ? "true" : "false") << std::endl;
		if (clientFd < 0)
		{
			Print::Fail("Couldn't accept connection");
			continue ;
		}

		Print::Ok("New connection accepted. FD: " + toString(clientFd));

		
		// Step 5: Receive data from client
		char buffer[BUFFER_SIZE] = {0};
		ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

		if (bytesRead > 0)
		{
			buffer[bytesRead] = '\0';
			Print::Debug("Recieved " + toString(bytesRead)
							+ " bytes from client FD: " + toString(clientFd)
							+ " -> " + buffer);
			
			// Echo back to client
			const char* response = "Message received!\n";
			send(clientFd, response, strlen(response), 0);
		}
		else if (bytesRead == 0)
			Print::StdOut("Client disconnected!");
		else
			Print::Error("Failed receiving data");

		// Step 6: Close client connection
		close(clientFd);
		Print::Ok("Client connection closed Succefully");
	}
}

void Server::cleanup()
{
	if (_fd != -1)
	{
		close(_fd);
		_fd = -1;
		Print::Ok("Server sockect closed Succefully");
	}
}