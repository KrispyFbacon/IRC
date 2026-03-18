#include "KickCommand.hpp"

// command = "KICK"
// param[0] = "#channel"
// param[1] = "nick"
// param[2] = ":reason ..."

void	KickCommand::execute(Server &server, Client &client, const Message &msg)
{
	std::string	channelName = msg.params[0];
	std::string	target = msg.params[1];
	std::string	reason = msg.params[2];

	const int	clientFd = client.getFd();

	Channel	*channel = server.getChannel(channelName);
	Client	*targetPointer = channel->getClientByNickname(target);

	// If channel exists
	if (!channel)
		sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + ":No such channel");

	// If kicker is in the channel
	if (!channel->getClient(clientFd))
		sendError(client, IRC::ERR_NOTONCHANNEL, channelName + ":You're not on that channel");

	// If kicker is a moderator
	if (!channel->getModerator(clientFd))
		sendError(client, IRC::ERR_CHANOPRIVSNEEDED, channelName + ":You're not channel operator");

	// If target exists and is in channel
	if (!channel->getClientByNickname(target))
		sendError(client, IRC::ERR_USERNOTINCHANNEL, target + " " + channelName + " :They aren't on that channel");

	// Broadcast then remove
	std::string	kickMsg = ":" + client.getNickname() + " KICK " + channelName + " " + target + " :" + reason;
	if (channel->getModerator(clientFd) != NULL)
		channel->removeModerator(clientFd);
	channel->removeClient(targetPointer->getFd());

	channel->broadcast(kickMsg);
}

