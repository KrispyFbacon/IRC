#include "JoinCommand.hpp"

void JoinCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("JOIN COMMAND CALLED!");

	// TODO prefix client?  return ":" + client.username
	(void)server;
	client.sendMessage(":" + client.getUsername() + " JOIN " + "#" + msg.target); // TODO channel name
	
	//TODO BRODCAST MESSAGE(client, channel, "brodcast message")?
	// :client + " JOIN " + channelName
	
}