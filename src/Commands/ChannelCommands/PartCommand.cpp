#include "PartCommand.hpp"
#include "Server.hpp"

// command = "PART"
// params[0] = "#channel"
// params[n] = can have more channel if separated by ","

static void leaveChannel(Server &server, Client &client, const std::string &channelName, const std::string &reason)
{
	Channel *channel = server.getChannel(channelName);

	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));

	if (!channel->getClient(client.getFd()))
		return (sendError(client, IRC::ERR_NOTONCHANNEL, channelName + " :You're not on that channel"));

	// Append reason if it exists!
	std::string partMsg = ":" + client.getPrefix() + " PART " + channelName;
	if (!reason.empty())
		partMsg += " :" + reason;

	channel->broadcast(partMsg);

	channel->removeClient(client.getFd());
	client.removeChannel(channelName);

	if (channel->getClients().empty())
		server.removeChannel(channel);
}

void	PartCommand::execute(Server &server, Client &client, const Message &msg)
{
	Print::Debug("PART Command Called!");

	if (msg.params.empty())
		return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "PART :Not enough parameters"));

	// Get optional reason
	std::string reason = "";
	if (msg.params.size() > 1)
		reason = msg.params[1];

	std::vector<std::string> channels = splitComma(msg.params[0]);
	for (size_t i = 0; i < channels.size(); ++i)
		leaveChannel(server, client, channels[i], reason);
}
