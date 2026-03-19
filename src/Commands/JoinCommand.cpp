#include "JoinCommand.hpp"

static bool isValidChannelName(const std::string& name)
{
	if (name.empty() || name[0] != '#' || name.size() < 2)
		return (false);
	for (size_t i = 1; i < name.size(); ++i)
	{
		if (name[i] == ' ' || name[i] == ',' || name[i] == '\a')
			return (false);
	}
	return (true);
}

static void sendNamesReply(Client& client, Channel* channel)
{
	const std::map<int, Client*>& clients    = channel->getClients();
	const std::map<int, Client*>& moderators = channel->getModerators();

	std::string list;
	std::map<int, Client*>::const_iterator it = clients.begin();
	for (; it != clients.end(); ++it)
	{
		if (!list.empty())
			list += " ";
		if (moderators.find(it->first) != moderators.end())
			list += "@";
		list += it->second->getNickname();
	}

	sendReply(client, IRC::RPL_NAMREPLY,   "= " + channel->getChannelName() + " :" + list);
	sendReply(client, IRC::RPL_ENDOFNAMES, channel->getChannelName() + " :End of NAMES list");
}

static void handleOneJoin(Server& server, Client& client,
						const std::string& rawJoin, const std::string& rawKey)
{
	// rawJoin = "JOIN #chan", rawKey = "PASS thekey" or "PASS "
	Message joinMsg = parseMessage(rawJoin);
	Message keyMsg  = parseMessage(rawKey);

	if (joinMsg.params.empty())
		return ;

	std::string channelName = joinMsg.params[0];
	std::string key         = keyMsg.params.empty() ? "" : keyMsg.params[0];

	if (!isValidChannelName(channelName))
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL,
						channelName + " :No such channel"));

	Channel* channel = server.getChannel(channelName);
	bool     isNew   = (channel == NULL);

	if (isNew)
	{
		// Create the channel and make the founder operator
		channel = server.createChannel(channelName);
		channel->addClient(client);
		channel->addModerator(client);
	}
	else
	{
		// Already in channel?
		if (channel->getClient(client.getFd()))
			return (sendError(client, IRC::ERR_USERONCHANNEL,
							client.getNickname() + " " + channelName + " :is already on channel"));

		// Invite-only?
		if (channel->getInviteOnly() && channel->getInvited(client.getNickname()).empty())
			return (sendError(client, IRC::ERR_INVITEONLYCHAN,
							channelName + " :Cannot join channel (+i)"));

		// Wrong key?
		if (!channel->getPass().empty() && channel->getPass() != key)
			return (sendError(client, IRC::ERR_BADCHANNELKEY,
							channelName + " :Cannot join channel (+k)"));

		// Full?
		if ((int)channel->getClients().size() >= channel->getUserLimit())
			return (sendError(client, IRC::ERR_CHANNELISFULL,
							channelName + " :Cannot join channel (+l)"));

		channel->addClient(client);
	}

	// Broadcast JOIN to everyone in channel (including the joiner)
	std::string joinMsg2 = ":" + client.getPrefix() + " JOIN " + channelName;
	channel->broadcast(joinMsg2);

	// Topic
	std::string topic = channel->getTopic();
	if (!topic.empty())
		sendReply(client, IRC::RPL_TOPIC, channelName + " :" + topic);
	else
		sendReply(client, IRC::RPL_NOTOPIC, channelName + " :No topic is set");

	// NAMES list
	sendNamesReply(client, channel);
}

void JoinCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug("JOIN COMMAND CALLED!");

	if (!client.isRegistered())
		return (sendError(client, IRC::ERR_NOTREGISTERED, ":You have not registered"));

	if (msg.params.empty())
		return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters"));

	// Re-assemble the raw line so parseJoinMessage can split channels/keys
	std::string raw = "JOIN " + msg.params[0];
	if (msg.params.size() > 1)
		raw += " " + msg.params[1];

	JoinMessage jm = parseJoinMessage(raw);

	for (size_t i = 0; i < jm.channels.size(); ++i)
		handleOneJoin(server, client, jm.channels[i], jm.keys[i]);
}