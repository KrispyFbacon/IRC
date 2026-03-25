#include "QuitCommand.hpp"
#include "Server.hpp"

void QuitCommand::execute(Server& server, Client& client, const Message& msg)
{
	(void)server;
	Print::Debug ("QUIT Command Called!");

	std::string reason = "Client Quit";
	if (!msg.params.empty())
		reason = msg.params[0];

	std::string errorMsg = "ERROR :Closing Link: (" + reason + ")";
	client.sendMessage(errorMsg);


	// Broadcast the QUIT
	if (client.isRegistered())
	{
		std::string broadcast = ":" + client.getPrefix() + " QUIT :Quit: " + reason;

		client.broadcast(broadcast);
	}

	client.setDisconnected(true);
}
