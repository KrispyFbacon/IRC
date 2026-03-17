#include "QuitCommand.hpp"

void QuitCommand::execute(Server& server, Client& client, const Message& msg)
{
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

		//TODO Broadcast quit message
	}


	client.setDisconnected(true);
}

// TODO broadcast type to all channels?
	// std::set<int> notifiedUsers;?
	// for (loop throught clients channels)
		// check if same fd -> continue
		// Check if already sent message to that fd

// TODO CAREFULL FOR LEAKS
	//TODO CHANNEL::removeClient (int fd)
		//_clients.erase(fd);
		//_moderators.erase(fd);
		// TODO CLIENT:: client->removeChannel(this->getName());?
				// _channels.erase(channelName);

	//TODO Client -> addChannel, removeChannel?
	//TODO Channel -> addClient, removeClient?

	// TODO Server::removeClient, QuitCommand, PartCommand, and KickCommand 
	//		will all just call Channel::removeClient(client)?
