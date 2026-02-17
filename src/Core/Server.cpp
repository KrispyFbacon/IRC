/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:35:52 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/17 18:06:14 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port) : _fd(-1), _port(port) {}

Server::~Server()
{
	cleanup();
}

// initServer
bool Server::initServer()
{
	// Create socket
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
	{
		Print::Error("Failed to create socket");
		return false;
	}

	int opt = 1;
	if (!setOption(SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		return false;

	// Set socket to non-blocking
	if (!setNonBlocking())
		return false;

	// Bind socket to address and port 
	// TODO maybe Adress:bind(port)
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(_port);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		Print::Error("Bind() failed");
		return false;
	}

	// Start listening
	// TODO maybe Adress:listen(backlog)
	int backlog = 10;
	if (listen(_fd, backlog) < 0)
	{
		Print::Error("Listen() failed");
		return false;
	}

	// TODO Create the epoll instance
	// TODO Register the listening socket with epoll

	Print::Ok("Server listening on port: " + toString(_port));

	return true;
}


// run
void Server::run()
{
	Print::Debug("Server running. Press Ctrl+C to stop.");

	while (g_running)
	{
		// Accept incoming connection
		struct sockaddr_in clientAdress;
		socklen_t clientLen = sizeof(clientAdress);

		int clientFd = accept(_fd, (struct sockaddr*)&clientAdress, &clientLen);
		//std::cout << "G_Running = " << (g_running ? "true" : "false") << std::endl;
		if (clientFd < 0)
		{
			//Print::Error("Couldn't accept connection");
			continue ;
		}

		Print::Ok("New connection accepted. FD: " + toString(clientFd));

		
		// Receive data from client
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

		// Close client connection
		close(clientFd);
		Print::Ok("Client connection closed Succefully");
	}
}


// cleanup
void Server::cleanup()
{
	if (_fd != -1)
	{
		close(_fd);
		_fd = -1;
		Print::Ok("Server sockect closed Succefully");
	}
}


// ── I/O helpers ─────────────────────────────────────────────────────────────

// Makes a file descriptor non-blocking
bool Server::setNonBlocking()
{
	int fdFlags = fcntl(_fd, F_GETFL, 0);
	if (fdFlags == -1)
	{
		Print::Error("fcntl() F_GETFL failed");
		return false;
	}

	if (fcntl(_fd, F_SETFL, fdFlags | O_NONBLOCK) == -1)
	{
		Print::Error("fcntl() F_SETFL failed");
		return false;
	}
	
	return true;
}

// Sets a socket options (e.g. SO_REUSEADDR)
bool Server::setOption(int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(_fd, level, optname, optval, optlen) < 0)
	{
		Print::Error("setsockopt() failed");
		return false;
	}

	return true;
}