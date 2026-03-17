#include "JoinCommand.hpp"


void JoinCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("JOIN COMMAND CALLED!");

	//TODO Registered?

	// TODO 
	// if (!client.isRegistered()) {
	// 	sendError(client, IRC::ERR_NOTREGISTERED, "JOIN :You have not registered");
	// 	return;
	// }

	// TODO prefix client?  return ":" + client.username
	// TODO WE HAVE PREFIX client.getPrefix();
	(void)server;
	client.sendMessage(":" + client.getUsername() + " JOIN " + "#" + msg.target); // TODO channel name // msg.params[1];
	
	//TODO BRODCAST MESSAGE(client, channel, "brodcast message")?
	// :client + " JOIN " + channelName

	//TODO COMMA HANDLER
	// std::vector<std::string> channels = splitArguments(message.getParams(0), ',');
	// std::vector<std::string> keys = (message.getSize() > 1 ?
	// 	splitArguments(message.getParams(1), ',') : std::vector<std::string>());

	// for (size_t i = 0; i < channels.size(); i++)
	// {
	// 	joinChannel(client, channels[i],
	// 				(i >= keys.size() ? "" : keys[i]));
	//}
	
}

// TODO ALL ERRORS
// ERR_NEEDMOREPARAMS	ERR_BANNEDFROMCHAN
// ERR_INVITEONLYCHAN	ERR_BADCHANNELKEY
// ERR_CHANNELISFULL	ERR_BADCHANMASK
// ERR_NOSUCHCHANNEL	ERR_TOOMANYCHANNELS
// RPL_TOPIC