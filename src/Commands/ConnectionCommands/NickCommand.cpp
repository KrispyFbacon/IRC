#include "NickCommand.hpp"

void NickCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("NICK Command Called!");

	// Check if Client is Authenticated
	if (client.isAuthenticated() == false)
		return(sendError(client, IRC::ERR_NOTREGISTERED, ":You have not register"));

	// Check if empty
	if (msg.params.empty() || msg.params[0].empty())
		return(sendError(client, IRC::ERR_NONICKNAMEGIVEN, ":No nickname given"));

	
	std::string newNick = msg.params[0];

	// Check if Nickname is valid
	if (!isValidNickname(newNick))
		return(sendError(client, IRC::ERR_ERRONEUSNICKNAME, newNick + " :Erroneus nickname"));

	// Check if NickName it's already taken!
	Client* existingClient = server.getClientByNickname(newNick);
	if (existingClient)
	{
		if (existingClient->getFd() == client.getFd())
			return ;
		
		return(sendError(client, IRC::ERR_NICKNAMEINUSE, newNick + " :Nickname is already in use"));
	}

	if (client.isRegistered())
	{
		std::string oldPrefix = client.getPrefix();

		std::string brodcast = ":" + oldPrefix + " NICK :" + newNick;

		client.sendMessage(brodcast);

		//TODO broadcast to all channels the user is in!
	}

	client.setNickname(newNick);

	server.checkRegistration(client);
}

