#include "UserCommand.hpp"

void UserCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("USER Command Called!");

	if (client.isAuthenticated() == false)
		return(sendError(client, IRC::ERR_NOTREGISTERED, ":You have not registered"));

	if (client.isRegistered() || !client.getUsername().empty())
		return(sendError(client, IRC::ERR_ALREADYREGISTRED, " :You cannot reregister"));

	if (msg.params.size() < 4 || (msg.params[0]).empty())
		return(sendError(client, IRC::ERR_NEEDMOREPARAMS, "USER :Not enough parameters"));

	std::string newUser = msg.params[0];

	client.setUsername(newUser);

	server.checkRegistration(client);
}

