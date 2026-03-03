#include "CommandFactory.hpp"

CommandFactory::CommandFactory()
{
	//TODO add other commands
	_commands["JOIN"] = &JoinCommand::make;
}

CommandFactory::~CommandFactory() {}

void CommandFactory::execute()
{
	//TODO Continue
	//commandIt it = _commands.find(msg.command);
	// if (it == _commands.end())
	// 	return; // THROW ERR_UNKNOWNCOMMAND 

	// ACommand* cmd = it->second();
	// cmd->execute(server, client, msg);

	// delete cmd;
}