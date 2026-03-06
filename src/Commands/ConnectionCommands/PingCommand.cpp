#include "PingCommand.hpp"

void PingCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PING Command Called!");

	(void)server;
	client.sendMessage(":42IRC PONG 42IRC :" + msg.target);
}