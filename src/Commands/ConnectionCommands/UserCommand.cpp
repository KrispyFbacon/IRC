#include "UserCommand.hpp"

void UserCommand::execute(Server& server, Client& client, const Message& msg)
{
	(void)server;
	Print::Debug ("USER Command Called!");


	if (client.isAuthenticated() || client.isRegistered())
	{
		sendError(client, IRC::ERR_ALREADYREGISTRED, " :You cannot reregister");
		return ;
	}

	if (msg.params.empty())
	{
		sendError(client, IRC::ERR_NEEDMOREPARAMS, " PASS :Not enough parameters");
		return ;
	}


	
	// TODO USER <username> <mode> <unused> :<realname>
	// TODO USER <username> * 0 :<realname>

	//TODO ALREADY REGISTED? IRC::ERR_ALREADYREGISTRED, "USER :Unauthorized command (already registered)""
	// TODO min 4 params
	// TODO client.setUserName param 0
	// PARAMS 1 2 IGNORE 3? IGNORE

	//TODO FULLY REGISTED?
		// trigger 001, 002, 003, 004 welcome messages!
}

