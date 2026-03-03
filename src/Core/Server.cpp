/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:35:52 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/26 17:52:42 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const std::string& port, const std::string& password)
	: _fd(-1), _epfd(-1), _port(port), _password(password) {}

Server::~Server()
{
	cleanup();
}


// initServer
void Server::initServer()
{
	// Create and bind the socket using our helper
	createAndBindSocket();

	// Set the listening socket to non-blocking
	setNonBlocking(_fd);

	// TODO maybe Socket::listen(backlog)
	// Start listening for incoming connections
	if (listen(_fd, BACKLOG) < 0)
		throw (SocketException("Listen() failed"));

	// Set up epoll and register the listening socket
	epollCreate(0);
	epollAdd(_fd, EPOLLIN);

	Print::Ok("Server listening on port: " + _port);
}

// run
void Server::run()
{
	Print::Debug("Server running. Press Ctrl+C to stop.");

	while (g_running)
	{
		// TODO save somewhere?
		epoll_event events[MAX_EVENTS];

		int nfds = epoll_wait(_epfd, events, MAX_EVENTS, -1);
		if (nfds == -1)
		{
			if (errno == EINTR) // signal interrupted wait
				continue;
			throw (EpollException("epoll_wait() failed"));
		}

		for (int n = 0; n < nfds; ++n)
		{
			int	currentFd = events[n].data.fd;
			uint32_t ev = events[n].events;
			
			try
			{
				if (currentFd == _fd)
				{
					handleNewConnection();
					continue;
				}

				// Error and HangUp
				if (ev & (EPOLLHUP | EPOLLRDHUP | EPOLLERR))
					// DEBUG
					throw ClientException("Client hangup FD: " + toString(currentFd));

				if (ev & EPOLLIN)
					handleClientMessage(currentFd);
			}
			catch (const SocketException& e)
			{
				Print::Warn(e.what());
			}
			catch (const EpollException& e)
			{
				Print::Warn(e.what());
			}
			catch (const ClientException& e)
			{
				Print::Warn(e.what());
				removeClient(currentFd);
			}
		}
	}
}

// cleanup
void Server::cleanup()
{
	// Client cleanup
	for (clientIt it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;
	_clients.clear();
	
	// Epoll fd
	if (_epfd != -1)
	{
		close(_epfd);
		_epfd = -1;
		Print::Debug("Epoll socket closed Succefully");
	}

	// Server fd
	if (_fd != -1)
	{
		close(_fd);
		_fd = -1;
		Print::Ok("Server socket closed Succefully");
	}
}



/* =========================== Client Management =========================== */

Client* Server::getClient(int clientFd)
{
	clientIt it = _clients.find(clientFd);

	if (it == _clients.end())
		return NULL;

	return it->second;
}



/* ================================= PRIVATE =============================== */


/* ============================== I/O helpers ============================== */

void Server::createAndBindSocket()
{
	struct addrinfo hints;

	std::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // Support both IPv4 and IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE; // Bind to all available interfaces

	
	// Get address information
	struct addrinfo* servinfo;
	if (getaddrinfo(NULL, _port.c_str(), &hints, &servinfo) != 0)
		throw SocketException("getaddrinfo() failed");

	// Loop through results and bind to the first working address
	struct addrinfo *p;
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (_fd == -1)
			continue;
		
		int opt = 1;
		if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) 
		{
			freeaddrinfo(servinfo);
			throw SocketException("setsockopt() failed");
		}

		if (bind(_fd, p->ai_addr, p->ai_addrlen) < 0) 
		{
			close(_fd);
			_fd = -1;
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo);
	
	if (p == NULL)
		throw SocketException("Failed to bind to any available address");
}

// Makes a file descriptor non-blocking
void Server::setNonBlocking(int fd)
{
	int fdFlags = fcntl(fd, F_GETFL, 0);
	if (fdFlags == -1)
		throw (SocketException("fcntl() F_GETFL failed"));

	if (fcntl(fd, F_SETFL, fdFlags | O_NONBLOCK) == -1)
		throw (SocketException("fcntl() F_SETFL failed"));
}

// Creates an epoll instance
void Server::epollCreate (int flags)
{
	_epfd = epoll_create1(flags);
	if (_epfd == -1)
		throw (EpollException("epoll_create1() failed"));
}

// Adds a fd to the epoll instance with specified events
void Server::epollAdd (int fd, uint32_t events)
{
	epoll_event ev;
	ev.events = events; 
	ev.data.fd = fd; // kernel hands this back to us when the event fires
	
	if (epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
		throw (EpollException("epoll_ctl ADD FD: " + toString(fd)));
}

// Modifies the events associated with a fd in the epoll instance
void Server::epollMod (int fd, uint32_t events)
{
	epoll_event ev;
	ev.events = events;
	ev.data.fd = fd;
	
	if (epoll_ctl(_epfd, EPOLL_CTL_MOD, fd, &ev) == -1)
		throw (EpollException("epoll_ctl MOD FD: " + toString(fd)));
}

// Removes a fd from the epoll instance
void Server::epollDel (int fd)
{
	if (epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL) == -1)
		throw (EpollException("epoll_ctl DEL FD: " + toString(fd)));
}




/* ============================ Event handlers ============================= */

void Server::handleNewConnection()
{
	while (true)
	{
		struct sockaddr_storage clientAdress;
		socklen_t clientLen = sizeof(clientAdress);
	
		int clientFd = accept(_fd, (struct sockaddr*)&clientAdress, &clientLen);
		if (clientFd == -1)
			return; // Can't use errno to loop!
		// if (clientFd == -1)
		// {
		// 	if (errno == EAGAIN || errno == EWOULDBLOCK)
		// 		break ;
		// 	throw(SocketException("accept() failed"));
		// }


		setNonBlocking(clientFd);
		epollAdd(clientFd, EPOLLIN);


		Client* newClient = new Client(clientFd);
		_clients[clientFd] = newClient;
		
		Print::Ok("Client connected FD: " + toString(clientFd));
	}
}

void Server::handleClientMessage(int clientFd)
{
	char buffer[BUFFER_SIZE] = {0};
	
	Client* client = getClient(clientFd);
	if (!client)
		throw ClientException("Client not found for FD: " + toString(clientFd));

	ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
			Print::Debug("No data available, but connection is still open");
			return;
		}
		throw ClientException("recv() failed FD: " + toString(clientFd));
	}

	if (bytesRead == 0)
	{
		Print::Debug("Client gracefully disconnected FD: " + toString(clientFd));
		removeClient(clientFd);
		return;
		
	}
	
	Print::Debug("Recieved " + toString(bytesRead)
						+ " bytes from client FD: " + toString(clientFd));
	
	//TODO maybe change to MessageParse class?
	client->appendBuffer(buffer, bytesRead);

	std::string line;
	while (client->getNextMessage(line))
	{
		// TODO Message and Command classes
		// Message msg = Message(line);
		// Command::execute(server, client, msg);
		
		Print::Debug("FD: " + toString(clientFd) + " -> [" + line + "]");
		
		// Echo back to client
		const char* response = "Message received!\r\n";
		send(clientFd, response, std::strlen(response), 0);
	
	}

	if (client->getBufferSize() > MAX_MESSAGE_SIZE)
	{
		client->clearBuffer();
		Print::Warn("Buffer overflow, clearing buffer of FD: " + toString(clientFd));
	}

}

void Server::removeClient(int fd)
{
	epollDel(fd);
	close(fd);
	
	clientIt it = _clients.find(fd);
	if (it != _clients.end())
	{
		delete it->second;
		_clients.erase(it); // Removes the entry from the map
	}
	
	Print::Debug("Client removed FD: " + toString(fd));
}