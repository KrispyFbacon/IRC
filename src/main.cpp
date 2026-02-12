/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:56:10 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/12 18:02:52 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "Server.hpp"

bool g_running = true;

void signalHandler(int signum)
{
	(void)signum;
	g_running = false;
}

int main(void)
{
	signal(SIGINT, signalHandler);

	Server server(PORT);
	
	if (!server.initServer())
	{
		return 1;
	}

	server.run();

	return 0;
}