#include "ModeKCommand.hpp"

// Direct call from ModeCommand with pre-parsed sign and key
void	ModeKCommand::execute(Client &client, Channel &channel, char sign, const std::string &key)
{
	const std::string	channelName = channel.getChannelName();
	const std::string	clientNick = client.getNickname();

	if (sign == '+')
	{
		if (key.empty())
			return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters"));
		if (!channel.getPass().empty())
			return (sendError(client, IRC::ERR_KEYSET, channelName + " :Channel key already set"));
		channel.setPass(key);
		channel.broadcast(":" + clientNick + " MODE " + channelName + " +k " + key);
	}
	else
	{
		channel.setPass("");
		channel.broadcast(":" + clientNick + " MODE " + channelName + " -k");
	}
}

// Standalone call: MODE #channel +k password  or  MODE #channel -k
void	ModeKCommand::execute(Server &server, Client &client, const Message &msg)
{
	if (msg.params.size() < 2)
		return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters"));

	const std::string	channelName = msg.params[0];
	const std::string	modeStr = msg.params[1];
	const std::string	key = (msg.params.size() > 2) ? msg.params[2] : "";

	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));
	if (!channel->getModerator(client.getFd()))
		return (sendError(client, IRC::ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator"));

	char	sign = (modeStr.size() > 0 && modeStr[0] == '-') ? '-' : '+';
	execute(client, *channel, sign, key);
}
