#include "KickCommand.hpp"

void	KickCommand::execute(Server &server, Client &client, const Message &msg)
{
	std::string	channelName = msg.target;
	std::string	targetNick, reason;
	parseKickParams(msg, targetNick, reason);

	// If channel exists
	Channel* channel = server.getChannel(channelName);
	if (!channel)
		return (client.sendMessage(":42IRC 403 " + client.getNickname() + " " + channelName + " :No such channel"));

	// If kicker is in the channel
	if (!channel->hasClient(client.getFd()))
		return (client.sendMessage(":42IRC 442 " + client.getNickname() + " " + channelName + " :You're not on that channel"));

	// If kicker is a moderator
	if (!channel->getModerator(client.getFd()))
		return (client.sendMessage(":42IRC 482 " + client.getNickname() + " " + channelName + " :You're not channel operator"));

	// If target exists and is in channel
	Client	*target = server.getClientByNick(targetNick);
	if (!target || !channel->hasClient(target->getFd()))
		return (client.sendMessage(":42IRC 441 " + client.getNickname() + " " + targetNick + " " + channelName + " :They aren't on that channel"));

	// If broadcast then remove
	std::string	kickMsg = ":" + client.getNickname() + " KICK " + channelName + " " + targetNick + " :" + reason;
	channel->broadcast(kickMsg);
	channel->removeClient(target);
}
