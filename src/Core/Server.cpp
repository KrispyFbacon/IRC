/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:35:52 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/19 14:20:40 by frbranda         ###   ########.fr       */
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
	if (!setNonBlocking(_fd))
		return false;

	// Bind socket to address and port 
	// TODO maybe Socket::bind(port)
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
	// TODO maybe Socket::listen(backlog)
	int backlog = 10;
	if (listen(_fd, backlog) < 0)
	{
		Print::Error("Listen() failed");
		return false;
	}

	// TODO Create the epoll instance
	if (!epollCreate(0))
		return false;
	
	// TODO Register the listening socket with epoll
	if (!epollAdd(_fd, EPOLLIN))
		return false;

	Print::Ok("Server listening on port: " + toString(_port));

	return true;
}

// run
void Server::run()
{
	Print::Debug("Server running. Press Ctrl+C to stop.");

	while (g_running)
	{
		// TODO save somewhere
		epoll_event events[MAX_EVENTS];

		int nfds = epoll_wait(_epfd, events, MAX_EVENTS, -1);
		if (nfds == -1)
		{
			if (errno == EINTR) // signal interrupted wait
				continue;
			Print::Error("epoll_wait() failed");
			break;
		}

		for (int n = 0; n < nfds; ++n)
		{
			int	currentFd = events[n].data.fd;
			
			if (currentFd == _fd)
				// TODO Accept incoming connection
				handleNewConnection();
			else
				// TODO Receive data from client
				handleClientMessage(currentFd);
			// TODO else - Disconnect Client // void removeClient(int fd);
			// TODO handle errors
			// TODO handle hangup with data available
			// TODO Handle hangup without data available
			}
	}
}

// cleanup
void Server::cleanup()
{
	if (_epfd != -1)
	{
		close(_fd);
		_fd = -1;
		Print::Debug("Epoll socket closed Succefully");
	}
	if (_fd != -1)
	{
		close(_fd);
		_fd = -1;
		Print::Ok("Server socket closed Succefully");
	}
}


// ── Client Management ───────────────────────────────────────────────────────

Client* Server::getClient(int clientFd)
{
	clientIt it = _clients.find(clientFd);

	if (it == _clients.end())
		return NULL;

	return it->second;
}



/* ================================= PRIVATE =============================== */

// ── I/O helpers ─────────────────────────────────────────────────────────────

// Makes a file descriptor non-blocking
bool Server::setNonBlocking(int fd)
{
	int fdFlags = fcntl(fd, F_GETFL, 0);
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

// Creates an epoll instance
bool Server::epollCreate (int flags)
{
	_epfd = epoll_create1(flags);
	
	if (_epfd == -1)
	{
		Print::Error("epoll_create1() failed");
		return false;
	}

	return true;
}

// Adds a fd to the epoll instance with specified events
bool Server::epollAdd (int fd, uint32_t events)
{
	epoll_event ev;
	ev.events = events; 
	ev.data.fd = fd; // kernel hands this back to us when the event fires
	
	if (epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
	{
		Print::Error("epoll_ctl ADD FD: " + toString(fd));
		return false;
	}

	return true;
}

// Modifies the events associated with a fd in the epoll instance
bool Server::epollMod (int fd, uint32_t events)
{
	epoll_event ev;
	ev.events = events;
	ev.data.fd = fd;
	
	if (epoll_ctl(_epfd, EPOLL_CTL_MOD, fd, &ev) == -1)
	{
		Print::Error("epoll_ctl MOD FD: " + toString(fd));
		return false;
	}

	return true;
}

// Removes a fd from the epoll instance
bool Server::epollDel (int fd)
{
	if (epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL) == -1)
	{
		Print::Error("epoll_ctl DEL FD: " + toString(fd));
		return false;
	}

	return true;
}


// ── Event handlers ──────────────────────────────────────────────────────────


void Server::handleNewConnection()
{
	while (true)
	{
		struct sockaddr_in clientAdress;
		socklen_t clientLen = sizeof(clientAdress);
	
		int clientFd = accept(_fd, (struct sockaddr*)&clientAdress, &clientLen);
		if (clientFd == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break ;
			Print::Error("accept() failed");
			break ;
		}

		setNonBlocking(clientFd);
		epollAdd(clientFd, EPOLLIN);

		// TODO Save client information into Client container
		Client* newClient = new Client(clientFd);
		_clients[clientFd] = newClient;
		
		Print::Ok("Client connected FD: " + toString(clientFd));
	}
}

void Server::handleClientMessage(int clientFd)
{
	char buffer[BUFFER_SIZE] = {0};
	
	
	
	ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead <= 0)
	{
		if (bytesRead == 0)
			Print::StdOut("Client disconnected FD: " + toString(clientFd));
		else
			Print::Error("recv() failed FD: " + toString(clientFd));

		removeClient(clientFd);
		return;
	}
	
	_clients[clientFd]->_buffer.append(buffer, bytesRead);

	// buffer[bytesRead] = '\0';
	// Print::Debug("Recieved " + toString(bytesRead)
	// 						+ " bytes from client FD: " + toString(clientFd)
	// 						+ " -> " + buffer);
			
	// // Echo back to client
	// const char* response = "Message received!\r\n";
	// send(clientFd, response, std::strlen(response), 0);

	
	// TODO Need to buffer per client
	// TODO This requires you to add _clients[clientFd] = Client(clientFd) in handleNewConnection and have a processMessage method.
	// TODO One message in → one reply out, regardless of how TCP fragments it.
	// _clients[clientFd].recv_buf.append(buffer, bytesRead);

    // // Only process complete IRC messages (terminated by \r\n)
    // size_t pos;
    // while ((pos = _clients[clientFd].recv_buf.find("\r\n")) != std::string::npos)
    // {
    //     std::string msg = _clients[clientFd].recv_buf.substr(0, pos);
    //     _clients[clientFd].recv_buf.erase(0, pos + 2);

    //     if (!msg.empty())
    //         processMessage(clientFd, msg);
    // }
}

void Server::removeClient(int fd)
{
	epollDel(fd);
	close(fd);
	_clients.erase(fd);
	Print::StdOut("Client removed FD: " + toString(fd));
}