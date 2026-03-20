#include "PrivmsgCommand.hpp"
#include "Server.hpp"

void NickCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PRIVMSG Command Called!");

	// Check for target and message paremeters
	if (msg.params.empty() < 2)
	{
		if (msg.params.empty() < 1 || msg.params[0].empty())
			return (sendError(client, IRC::ERR_NORECIPIENT, ":No recipient given (PRIVMSG)"));
		else
			return (sendError(client, IRC::ERR_NOTEXTTOSEND, ":No text to send"));
	}

	std::string target = msg.params[0];
	std::string text = msg.params[1];
}