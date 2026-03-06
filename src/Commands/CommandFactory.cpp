#include "CommandFactory.hpp"

CommandFactory::CommandFactory()
{
	//TODO add other commands

	// Connection Commands
	_commands["PING"] = &PingCommand::make;

	// Channels Commands
	_commands["JOIN"] = &JoinCommand::make;
}

CommandFactory::~CommandFactory() {}

void CommandFactory::execute(Server& server, Client& client, const Message& msg)
{
	//TODO Continue
	CommandIt it = _commands.find(msg.command);
	if (it == _commands.end())
	{
		Print::Debug("Unknown command '" + msg.command + "' from FD: " + toString(client.getFd()));

		// TODO Error Message handler
		sendError(client, IRC::ERR_UNKNOWNCOMMAND, msg.command + " :Unknown command");
		return;
	}
	

	ACommand* cmd = it->second();
	cmd->execute(server, client, msg);

	delete cmd;
}

//std::string errorMsg = ":" + server._hostName + " PONG " + server._hostName + 421 "