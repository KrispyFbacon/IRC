#include "KickCommand.hpp"
#include "Server.hpp"

// command = "KICK"
// params[0] = "#channel"
// params[1] = "nick1,nick2,nickN"
// params[2] = ":reason ..."  (optional)

static void	kickTarget(Client &client, Channel *channel, const std::string &target, const std::string &reason)
{
	const std::string	channelName = channel->getChannelName();

	Client	*targetClient = channel->getClientByNickname(target);
	if (!targetClient)
		return (sendError(client, IRC::ERR_USERNOTINCHANNEL,
						target + " " + channelName + " :They aren't on that channel"));

	// Broadcast BEFORE removing so the kicked user receives it
	std::string	kickMsg = ":" + client.getNickname()
						+ " KICK " + channelName
						+ " " + target
						+ " :" + reason;
	channel->broadcast(kickMsg);

	// Remove from moderators if they were one
	if (channel->getModerator(targetClient->getFd()))
		channel->removeModerator(targetClient->getFd());

	channel->removeClient(targetClient->getFd());
	targetClient->removeChannel(channelName);
}

void	KickCommand::execute(Server &server, Client &client, const Message &msg)
{
	Print::Debug("KICK COMMAND CALLED!");

	if (msg.params.size() < 2)
		return (sendError(client, IRC::ERR_NEEDMOREPARAMS,
						"KICK :Not enough parameters"));

	const std::string	channelName = msg.params[0];
	const std::string	reason = (msg.params.size() > 2) ? msg.params[2] : "No reason given";
	const int	clientFd = client.getFd();

	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL,
						channelName + " :No such channel"));

	if (!channel->getClient(clientFd))
		return (sendError(client, IRC::ERR_NOTONCHANNEL,
						channelName + " :You're not on that channel"));

	if (!channel->getModerator(clientFd))
		return (sendError(client, IRC::ERR_CHANOPRIVSNEEDED,
						channelName + " :You're not channel operator"));

	argumentSplit	split = splitParse(msg);

	for (size_t i = 0; i < split.targets.size(); ++i)
	{
		std::string	pass = (i < split.keys.size()) ? split.keys[i] : "";
		kickTarget(client, channel, split.targets[i], reason);
	}
}
