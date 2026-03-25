#include "PartCommand.hpp"
#include "Server.hpp"

// command = "PART"
// params[0] = "#channel"
// params[n] = can have more channel if separated by ","

static void	leaveChannel(Server server, Client &client, const std::string channelName)
{
	Channel *channel = server.getChannel(channelName);

	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));

	if (!channel->getClient(client.getFd()))
		return (sendError(client, IRC::ERR_NOTONCHANNEL, channelName + " :You're not on that channel"));

	channel->broadcast(":" + client.getPrefix() + " PART " + channelName);

	channel->removeClient(client.getFd());
	client.removeChannel(channelName);

	if (channel->getClients().empty())
		server.removeChannel(channel);
}

void PartCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PART Command Called!");

	std::string	targetName = msg.params[0];
	std::string	channelName = msg.params[1];

	if (msg.params.empty())
		return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "PART :Not enough parameters"));

	std::vector<std::string>	channels = splitComma(msg.params[0]);
	for (size_t i = 0; i < channels.size(); ++i)
		leaveChannel(server, client, channels[i]);

	Print::Ok("Client FD: " + toString(client.getFd()) + " is Authenticated");
}
