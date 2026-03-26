#include "InviteCommand.hpp"
#include "Server.hpp"

// command = "INVITE"
// target  = "nickname"
// message = "#channel ..."

void	InviteCommand::execute(Server &server, Client &client, const Message &msg)
{
	if (msg.params.size() < 2 || msg.params[0].empty() || msg.params[1].empty())
			return sendError(client, IRC::ERR_NEEDMOREPARAMS, "INVITE :Not enough parameters");

	std::string	targetName = msg.params[0];
	std::string	channelName = msg.params[1];

	
	// If channel exists
	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));

	// Inviter is in the channel?
	if (!channel->getClient(client.getFd()))
		return (sendError(client, IRC::ERR_NOTONCHANNEL,
				channelName + " :You're not on that channel"));

	// Channel Invite Only (+i)?
	if (channel->getInviteOnly() && !channel->getModerator(client.getFd()))
		return (sendError(client, IRC::ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator"));

	// Target user exists?
	Client	*target = server.getClientByNickname(targetName);
	if (!target || !target->isRegistered())
		return (sendError(client, IRC::ERR_NOSUCHNICK, targetName + " :No such nick"));

	// If target already in channel
	Client	&targetRef = *target;
	if (channel->getClient(targetRef.getFd()))
		return (sendError(client, IRC::ERR_USERONCHANNEL, targetName + " " + channelName + " :is already on channel"));

	// Send invite to target + confirmation to inviter
	target->sendMessage(":" + client.getPrefix() + " INVITE " + targetName + " :" + channelName);

	channel->addInvited(targetName);

	return (sendReply(client, IRC::RPL_INVITING, channelName + " " + targetName));
}
