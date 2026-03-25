#include "CommandFactory.hpp"

CommandFactory::CommandFactory()
{
	// Connection Commands
	_commands["NICK"] = &NickCommand::make;
	_commands["PASS"] = &PassCommand::make;
	_commands["PING"] = &PingCommand::make;
	_commands["PONG"] = &PongCommand::make;
	_commands["QUIT"] = &QuitCommand::make;
	_commands["USER"] = &UserCommand::make;
	_commands["PART"] = &PartCommand::make;

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
	CommandIt it = _commands.find(msg.command);
	if (it == _commands.end())
	{
		Print::Debug("Unknown command '" + msg.command + "' from FD: " + toString(client.getFd()));

		sendError(client, IRC::ERR_UNKNOWNCOMMAND, msg.command + " :Unknown command");
		return;
	}

	// Verify if registered!
	if (!client.isRegistered() && !isConnectionCommands(msg.command))
		return(sendError(client, IRC::ERR_NOTREGISTERED, ":You have not registered"));

	ACommand* cmd = it->second();
	cmd->execute(server, client, msg);

	delete cmd;
}