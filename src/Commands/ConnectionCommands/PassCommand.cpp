#include "PassCommand.hpp"

void PassCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PASS Command Called!");

	if (client.isAuthenticated() || client.isRegistered())
		return(sendError(client, IRC::ERR_ALREADYREGISTRED, " :You cannot reregistered"));


	if (msg.params.empty())
		return(sendError(client, IRC::ERR_NEEDMOREPARAMS, "PASS :Not enough parameters"));


	if (msg.params[0] != server.getPassword())
		return(sendError(client, IRC::ERR_PASSWDMISMATCH, " :Password incorrect"));
 
	client.setAuthenticated(true);

	Print::Ok("Client FD: " + toString(client.getFd()) + " is Authenticated");
}