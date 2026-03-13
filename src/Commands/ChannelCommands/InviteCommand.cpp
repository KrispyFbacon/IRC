#include "InviteCommand.hpp"

// command = "INVITE"
// target  = "nickname"
// message = "#channel ..."

void	InviteCommand::execute(Server &server, Client &client, const Message &msg)
{
	std::string	channelName = msg.params[0];
	std::string	targetName = msg.params[1];
	std::string	channelName = msg.params[2];

	const int	clientFd = client.getFd();

	// If channel exists
	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel");

	// Inviter is in the channel?
	if (!channel->getClient(client.getFd()))
		sendError(client, IRC::ERR_NOTONCHANNEL, channelName + " :You're not on that channel");

	// Target user exists?
	Client	*target = server.getClientByNickname(targetName);
	if (!target)
		sendError(client, IRC::ERR_NOSUCHNICK, targetName + " :No such nick");

	// If target already in channel
	if (channel->getClient(client.getFd()))
		sendError(client, IRC::ERR_USERONCHANNEL, targetName + " " + channelName + " :is already on channel");

	// Send invite to target + confirmation to inviter
	target->sendMessage(":" + client.getNickname() + " INVITE " + targetName + " :" + channelName);
	sendError(client, IRC::RPL_INVITING, targetName + " :" + channelName);
}
