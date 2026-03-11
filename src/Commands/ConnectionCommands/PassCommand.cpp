#include "PassCommand.hpp"

void PassCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PASS Command Called!");

	if (client.isAuthenticated() || client.isRegistered())
	{
		sendError(client, IRC::ERR_ALREADYREGISTRED, " :You cannot reregister");
		return ;
	}

	if (msg.params.empty())
	{
		sendError(client, IRC::ERR_NEEDMOREPARAMS, " PASS :Not enough parameters");
		return ;
	}

	if (msg.params[0] != server.getPassword())
	{
		sendError(client, IRC::ERR_PASSWDMISMATCH, " :Password incorrect");
		return ;
	}

	client.setAuthenticated(true);

	Print::Ok("Client FD: " + toString(client.getFd()) + " is Authenticated");
}