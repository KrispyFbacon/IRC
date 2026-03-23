#include "CommandFactory.hpp"

CommandFactory::CommandFactory()
{
	//TODO add other commands

	// Connection Commands
	_commands["NICK"] = &NickCommand::make;
	_commands["PASS"] = &PassCommand::make;
	_commands["PING"] = &PingCommand::make;
	_commands["PONG"] = &PongCommand::make;
	_commands["QUIT"] = &QuitCommand::make;
	_commands["USER"] = &UserCommand::make;

	// Channels Commands
	_commands["JOIN"] = &JoinCommand::make;
	_commands["MODE"] = &ModeCommand::make;
	_commands["INVITE"] = &InviteCommand::make;
	_commands["KICK"] = &KickCommand::make;
	_commands["TOPIC"] = &TopicCommand::make;
	_commands["PRIVMSG"] = &PrivmsgCommand::make;
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

	// Verify if registered!
	/* bool test1 = client.isRegistered();
	bool test2 = isConnectionCommands(msg.command);
	Print::Debug("test1 = isRegisted: '" + toString(test1));
	Print::Debug("test2 = isConnectionCommands: '" + toString(test2)); */

	if (!client.isRegistered() && !isConnectionCommands(msg.command))
		return(sendError(client, IRC::ERR_NOTREGISTERED, ":You have not registered"));

	ACommand* cmd = it->second();
	cmd->execute(server, client, msg);

	delete cmd;
}