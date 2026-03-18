#include "PingCommand.hpp"
#include "Server.hpp"

void PingCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PING Command Called!");

	(void)server;
	std::string pongMsg = ":" + Config::SERVER_NAME + " PONG " + Config::SERVER_NAME + " :";

	//TODO verifications
	
	client.sendMessage(pongMsg + msg.params[0]); // msg.params[0];
}