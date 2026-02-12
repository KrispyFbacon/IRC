/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:37:03 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/12 17:27:44 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Utils.hpp"

class Server
{
	private:
		int _fd;
		int _port;
		
	public:
		Server(int port);
		~Server();

		bool initServer();
		void run();
		void cleanup();
};

#endif