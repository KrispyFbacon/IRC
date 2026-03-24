#include "PrivmsgCommand.hpp"
#include "Server.hpp"

void PrivmsgCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PRIVMSG Command Called!");

	// Check for target and message paremeters
	if (msg.params.empty() || msg.params[0].empty())
		return (sendError(client, IRC::ERR_NORECIPIENT, ":No recipient given (PRIVMSG)"));

	if (msg.params.size() < 2 || msg.params[1].empty())
		return (sendError(client, IRC::ERR_NOTEXTTOSEND, ":No text to send"));


	std::vector<std::string> targets = splitComma(msg.params[0]);

	for (size_t i = 0; i < targets.size(); ++i)
	{
		if (targets[i][0] == '#' || targets[i][0] == '&')
			handleChannelMessage(server, client, targets[i], msg.params[1]);
		else
			handlePrivateMessage(server, client, targets[i], msg.params[1]);
	}
}

/* ================================= PRIVATE =============================== */

void PrivmsgCommand::handleChannelMessage(Server& server, Client& client, const std::string& channelName, const std::string& msg)
{
	// Check if channel exists
	Channel* channel = server.getChannel(channelName);
	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));

	// Check if sender is in the channel
	if (!channel->getClient(client.getFd()))
		return(sendError(client, IRC::ERR_CANNOTSENDTOCHAN, channelName + " :Cannot send to channel"));

	// Broadcast to everyone in the Channel EXCEPT the sender
	std::string broadcastMsg = ":" + client.getPrefix() + " PRIVMSG " + channelName + " :" + msg;
	channel->broadcast(broadcastMsg, client.getFd());
	
	Print::Ok("Broadcasted message from " NUM_COLOR + client.getNickname() + RST + " to " + NUM_COLOR + channelName);
}

void PrivmsgCommand::handlePrivateMessage(Server& server, Client& sender, const std::string& targetNick, const std::string& msg)
{
	// Check if target exists
	Client* target = server.getClientByNickname(targetNick);
	if (!target)
		return (sendError(sender, IRC::ERR_NOSUCHNICK, targetNick + " :No such nick/channel"));
	
	// Send the message!
	std::string dmMsg = ":" + sender.getPrefix() + " PRIVMSG " + sender.getNickname() + " :" + msg;
	target->sendMessage(dmMsg);
	

	Print::Ok("DM from " NUM_COLOR + sender.getNickname() + RST + " to " + NUM_COLOR + targetNick);
}

