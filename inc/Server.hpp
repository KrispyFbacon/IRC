/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:37:03 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/18 13:00:14 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Utils.hpp"


// ── Per-client ──────────────────────────────────────────────────────────────
class Client
{
	//int		fd;
	
	//clientStatus (class)
		// bool isRegisted (maybe just check if the variables are not empty)
		// bool hasUsername
		// bool hasPassword
		// bool hasNickName
	// create and destroy (class)
	
	//Message (class)
		//std::string recv_buf; // IRC messages end with \r\n
		//std::string send_buf; // holds data queued to send (drain it when EPOLLOUT fires)
};


// ── Server ──────────────────────────────────────────────────────────────────
class Server
{
	private:
		// Socket _serverSocked(); TODO maybe since server and clients will have their own socket
		int _fd; // serverFd
		int _epfd; // poll fd
		int _port;
		//std::map<int, Client>	_clients;

		// TODO I/O helpers
			bool setOption(int level, int optname, const void *optval, socklen_t optlen);
			bool setNonBlocking(int fd);
			bool epollCreate (int flags);
			bool epollAdd (int fd, uint32_t events);
			bool epollMod (int fd, uint32_t events);
			bool voidDel (int fd);

		// TODO Event handlers
			void handleNewConnection();
			void handleClientRead(int fd);
			//void handleClientWrite(int fd);
			void disconnectClient(int fd);

		// TODO IRC logic (Parsing)
			// void processMessage(int fd, const std::string& msg);
		
	public:
		Server(int port);
		~Server();

		bool initServer();
		void run();
		void cleanup();
};

#endif

// #define MAX_EVENTS 10

// struct epoll_event ev, events[MAX_EVENTS];
// int listen_sock, conn_sock, nfds, epollfd;

// /* Code to set up listening socket, 'listen_sock',
// 	(socket(), bind(), listen()) omitted */

// epollfd = epoll_create1(0);
// if (epollfd == -1) {
// 	perror("epoll_create1");
// 	exit(EXIT_FAILURE);
// }

// ev.events = EPOLLIN;
// ev.data.fd = listen_sock;
// if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
// 	perror("epoll_ctl: listen_sock");
// 	exit(EXIT_FAILURE);
// }

// for (;;) {
// 	nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
// 	if (nfds == -1) {
// 		perror("epoll_wait");
// 		exit(EXIT_FAILURE);
// 	}

// 	for (n = 0; n < nfds; ++n) {
// 		if (events[n].data.fd == listen_sock) {
// 			conn_sock = accept(listen_sock,
// 								(struct sockaddr *) &addr, &addrlen);
// 			if (conn_sock == -1) {
// 				perror("accept");
// 				exit(EXIT_FAILURE);
// 			}
// 			setnonblocking(conn_sock);
// 			ev.events = EPOLLIN | EPOLLET;
// 			ev.data.fd = conn_sock;
// 			if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
// 						&ev) == -1) {
// 				perror("epoll_ctl: conn_sock");
// 				exit(EXIT_FAILURE);
// 			}
// 		} else {
// 			do_use_fd(events[n].data.fd);
// 		}
// 	}
// }