#include "JoinCommand.hpp"


void JoinCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("JOIN COMMAND CALLED!");

	//TODO Registered?
	//TODO not enough params		-> ERR_NEEDMOREPARAMS
	//TODO Split argument with ',' channel/key
	//TODO isValidChannelName		-> ERR_NOSUCHCHANNEL
	//TODO GetChannel
		// Channel exists?
			// Create Channel
			// Channel limit?
		//else
			// already in channel?	-> ERR_USERONCHANNEL
			// is invite only?		-> ERR_INVITEONLYCHAN
			// has Password?		-> ERR_BADCHANNELKEY
			// is it Full?			-> ERR_CHANNELISFULL
			// channel.AddClient(client)?
			// client.sendMessage(joinMessage)?
			// channel.broadcast(joinMessage)?

		// TOPIC EMPTY?
			// sendReply(client, RPL_TOPIC, channelName + " :" + channel->getTopic());
		//else
			// sendReply(client, RPL_NOTOPIC, channelName + " :No topic is set");
		
		// send Channel List?
			// channel or client exist?
				//return
			// loop throw channel -> user
				// is channel->isModerator / find in channel._moderators
				// get nickName();
			// Send List
				// sendReply(client, IRC::RPL_NAMREPLY, "= " + channel->getName() + " :" + list);
				// sendReply(client, IRC::RPL_ENDOFNAMES, channel->getName() + " :End of NAMES list");



	// TODO 
	// if (!client.isRegistered()) {
	// 	sendError(client, IRC::ERR_NOTREGISTERED, "JOIN :You have not registered");
	// 	return;
	// }

	// TODO prefix client?  return ":" + client.username
	// TODO WE HAVE PREFIX client.getPrefix();
	(void)server;
	client.sendMessage(":" + client.getUsername() + " JOIN " + "#" + msg.params[0]); // TODO channel name // msg.params[1];
	//std::string joinMessage =":" + client->getNickname() + " JOIN :" + channelName";

	//TODO BRODCAST MESSAGE(client, channel, "brodcast message")?
	// :client + " JOIN " + channelName

	//TODO SPLIT
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