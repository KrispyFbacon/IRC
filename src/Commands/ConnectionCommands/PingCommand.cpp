#include "PingCommand.hpp"
#include "Server.hpp"

void PingCommand::execute(Server& server, Client& client, const Message& msg)
{
	(void)server;
	Print::Debug ("PING Command Called!");

	if (msg.params.empty() || msg.params[0].empty())
		return(sendError(client, IRC::ERR_NOORIGIN, ":No origin specified"));


	std::string pongMsg = ":" + Config::SERVER_NAME + " PONG " + Config::SERVER_NAME + " :";
	
	client.sendMessage(pongMsg + msg.params[0]);
}