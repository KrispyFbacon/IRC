#include "CommandFactory.hpp"

CommandFactory::CommandFactory()
{
	//TODO add other commands
	_commands["JOIN"] = &JoinCommand::make;
}

CommandFactory::~CommandFactory() {}

void CommandFactory::execute(Server& server, Client& client, const Message& msg)
{
	//TODO Continue
	CommandIt it = _commands.find(msg.command); // TODO toupper?
	if (it == _commands.end())
	{
		Print::Debug("Unknown command '" + msg.command + "' from FD: " + toString(client.getFd()));

		// TODO error Message handler
		std::string errorMsg = ":42IRC 421 "; // ERR_UNKNOWNCOMMAND
		//errorMsg += (client.getNickname().empty() ? "*" : client.getNickname());

		if (client.getNickname().empty())
			errorMsg += "*";
		else
			errorMsg += client.getNickname();
		
		errorMsg += " " + msg.command + " :Unknown command\r\n";
		client.sendMessage(errorMsg);
		return;
	}

	ACommand* cmd = it->second();
	cmd->execute(server, client, msg);

	delete cmd;
}