/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:56:10 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/11 18:22:55 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "Server.hpp"

int main(void)
{
	Server server(PORT);
	
	if (!server.initServer())
	{
		return 1;
	}
}