#include "InviteCommand.hpp"

// command = "INVITE"
// target  = "nickname"
// message = "#channel ..."

void	InviteCommand::execute(Server &server, Client &client, const Message &msg)
{
	std::string	targetNick = msg.target;
	std::string	channelName = msg.message;

	// If channel exists
	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (client.sendMessage(":42IRC 403 " + client.getNickname() + " " + channelName + " :No such channel"));

	// Inviter is in the channel?
	if (!channel->hasClient(client.getFd()))
		return (client.sendMessage(":42IRC 442 " + client.getNickname() + " " + channelName + " :You're not on that channel"));

	// Target user exists?
	Client	*target = server.getClientByNick(targetNick);
	if (!target)
		return (client.sendMessage(":42IRC 401 " + client.getNickname() + " " + targetNick + " :No such nick"));

	// If target already in channel
	if (channel->hasClient(target->getFd()))
		return (client.sendMessage(":42IRC 443 " + client.getNickname() + " " + targetNick + " " + channelName + " :is already on channel"));

	// Send invite to target + confirmation to inviter
	target->sendMessage(":" + client.getNickname() + " INVITE " + targetNick + " :" + channelName);
	client.sendMessage(":42IRC 341 " + client.getNickname() + " " + targetNick + " :" + channelName);
}
