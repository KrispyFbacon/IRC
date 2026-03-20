#include "JoinCommand.hpp"
#include "Server.hpp"

// command = "JOIN"
// params[0] = "ch1,ch2,chN"
// params[1] = "pass1,pass2,passN"  (optional)

static void	sendNamesReply(Client &client, Channel *channel)
{
	const std::map<int, Client *>	&clients = channel->getClients();
	const std::map<int, Client *>	&moderators = channel->getModerators();

	std::string list;
	for (std::map<int, Client *>::const_iterator it = clients.begin();
		 it != clients.end(); ++it)
	{
		if (!list.empty())
			list += " ";
		if (moderators.find(it->first) != moderators.end())
			list += "@";
		list += it->second->getNickname();
	}

	sendReply(client, IRC::RPL_NAMREPLY,
			  "= " + channel->getChannelName() + " :" + list);
	sendReply(client, IRC::RPL_ENDOFNAMES,
			  channel->getChannelName() + " :End of NAMES list");
}

static void	joinChannel(Server &server, Client &client,
						const std::string &channelName, const std::string &pass)
{
	if (!isValidChannelName(channelName))
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));

	Channel	*channel = server.getChannel(channelName);
	if (!channel)
	{
		// Channel doesn't exist — create it and make the founder operator
		channel = server.createChannel(channelName);
		channel->addClient(client);
		channel->addModerator(client);
	}
	else
	{
		// Already in channel?
		if (channel->getClient(client.getFd()))
			return sendError(client, IRC::ERR_USERONCHANNEL,
							 client.getNickname() + " " + channelName
							 + " :is already on channel");

		// Invite-only?
		if (channel->getInviteOnly() && channel->getInvited(client.getNickname()).empty())
			return sendError(client, IRC::ERR_INVITEONLYCHAN,
							 channelName + " :Cannot join channel (+i)");

		// Wrong key?
		if (!channel->getPass().empty() && channel->getPass() != pass)
			return sendError(client, IRC::ERR_BADCHANNELKEY,
							 channelName + " :Cannot join channel (+k)");

		// Channel full?
		if (static_cast<int>(channel->getClients().size()) >= channel->getUserLimit())
			return sendError(client, IRC::ERR_CHANNELISFULL,
							 channelName + " :Cannot join channel (+l)");
		
		channel->addClient(client);
	}

	// Broadcast JOIN to everyone in the channel (including the joiner)
	std::string	joinMsg = ":" + client.getPrefix() + " JOIN " + channelName;
	channel->broadcast(joinMsg);

	// Topic
	std::string	topic = channel->getTopic();
	if (!topic.empty())
		sendReply(client, IRC::RPL_TOPIC, channelName + " :" + topic);
	else
		sendReply(client, IRC::RPL_NOTOPIC, channelName + " :No topic is set");

	// NAMES list
	sendNamesReply(client, channel);
	Print::Ok(joinMsg);
}

void	JoinCommand::execute(Server &server, Client &client, const Message &msg)
{
	Print::Debug("JOIN COMMAND CALLED!");

	if (msg.params.empty())
		return sendError(client, IRC::ERR_NEEDMOREPARAMS,
						 "JOIN :Not enough parameters");


	std::vector<std::string> targets = splitComma(msg.params[0]);
	std::vector<std::string> keys;

	if (msg.params.size() > 1 && !msg.params[1].empty())
		keys = splitComma(msg.params[1]);


	for (size_t i = 0; i < targets.size(); ++i)
	{
		std::string	pass = (i < keys.size()) ? keys[i] : "";
		joinChannel(server, client, targets[i], pass);
	}
}