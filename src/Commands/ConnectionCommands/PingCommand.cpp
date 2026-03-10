#include "PingCommand.hpp"

void PingCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PING Command Called!");

	(void)server;
	std::string pongMsg = ":" + Config::SERVER_NAME + " PONG " + Config::SERVER_NAME + " :";

	client.sendMessage(pongMsg + msg.target); // msg.params[0];
}