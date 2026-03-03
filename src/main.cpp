/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:56:10 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/26 12:40:14 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "Server.hpp"

bool g_running = true;

void sigHandler(int signum)
{
	(void)signum;
	g_running = false;
}


int main(int argc, char* argv[])
{
	signal(SIGINT, sigHandler);
	signal(SIGTERM, sigHandler);

	if (argc != 3)
	{
		Print::InputError("Invalid Input");
		return 1;
	}

	std::string port(argv[1]);
	if (!isValidPort(port))
	{
		Print::InputError("Invalid Port");
		return 1;
	}
	
	std::string password(argv[2]);
	if (!isValidPassword(password))
	{
		Print::InputError("Invalid Password (Cannot be empty or contain spaces)");
		return 1;
	}

	
	try
	{
		Server server(port, password);
		server.initServer();
		server.run();
	}
	catch(const ServerException& e)
	{
		Print::Error(e.what());
		return 1;
	}
	catch (const std::exception& e)
	{
		Print::Error(std::string("Unexpected error: ") + e.what());
		return 1;
	}
	catch(...)
	{
		Print::Error("An unknown error occurred.");
		return 1;
	}
	
	
	return 0;
}

//SERVER CLASS
// TODO Socket class?
// TODO Epoll class/struct? with inBuffer and outBuffer?

// CHANNEL CLASS
// TODO Invite only flag
// TODO Password
// TODO Operator priveledge (if topic / password can be changed by non-moderators)
// TODO Channel Client limit
// TODO List of moderators

// CLIENT CLASS
// TODO ClientStatus class?
