#include "JoinCommand.hpp"


void JoinCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("JOIN COMMAND CALLED!");

	//TODO Registered? ✅ Done before execute

	if (msg.params.empty() || msg.params[0].empty())
        return(sendError(client, IRC::ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters"));

	//TODO Split argument with ',' channel/key

	for (size_t i = 0; i < channels.size(); i++)
	{
		joinChannel(client, channels[i], (i >= keys.size() ? "" : keys[i]));
	}



	// TODO prefix client?  return ":" + client.username
	// TODO WE HAVE PREFIX client.getPrefix();

	//(void)server;
	//client.sendMessage(":" + client.getUsername() + " JOIN " + "#" + msg.params[0]); // TODO channel name // msg.params[1];
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


void	JoinCommand::joinChannel(Server& server, Client& client, const std::string& channelName, const std::string& key)
{
	//TODO isValidChannelName		-> ERR_NOSUCHCHANNEL
		// TODO
		// <2 - FALSE
		// channelName[0] != '#' && channelName[0] != '&'?
		// Check for invalid characters in channel name
	if (isValidChannelName(const std::string& channelName) cons)) // in Acommand?
		return(sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));

	//TODO GetChannel
	Channel* channel = server.getChannel(channelName);

		// Channel exists?
		if(!channel)
		{
			// -> Create new Channel
            // -> Add Channel to Server's map
            // -> channel.addClient(client)
            // -> channel.addModerator(client) // Creator becomes moderator
            // -> client.addChannel(channel)
		}
		//else
		{
			// already in channel?	-> ERR_USERONCHANNEL
			// is invite only?		-> ERR_INVITEONLYCHAN
			// has Password?		-> ERR_BADCHANNELKEY
			// is it Full?			-> ERR_CHANNELISFULL
			// channel.AddClient(client)?
			// -> chan.removeInvite(client.getNickname()) <-- Consume ticket!
			// client.sendMessage(joinMessage)?
		}

		//TODO broadcast channel
		// chan.broadcast(":" + client.getNickName() + " JOIN :" + chanName); // client.getPrefix()?

		//TODO send topic
			if (chan.getTopic().empty())
				sendReply(client, IRC::RPL_NOTOPIC, channelName + " :No topic is set");
			else
				sendReply(client, RPL_TOPIC, channelName + " :" + channel->getTopic());
		
		// send Channel List?
			// channel or client exist?
				//return
			// loop throw channel -> user
				// is channel->isModerator // find in channel._moderators add '@'
				// get nickName();
			// Send List
				// sendReply(client, IRC::RPL_NAMREPLY, "= " + channel->getName() + " :" + list);
				// sendReply(client, IRC::RPL_ENDOFNAMES, channel->getName() + " :End of NAMES list");
	

}