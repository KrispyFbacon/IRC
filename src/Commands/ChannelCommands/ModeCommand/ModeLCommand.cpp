#include "ModeLCommand.hpp"

// Direct call from ModeCommand with pre-parsed sign and limit string
void	ModeLCommand::execute(Client &client, Channel &channel, char sign, const std::string &limitStr)
{
	const std::string	channelName = channel.getChannelName();
	const std::string	clientNick = client.getNickname();

	if (sign == '+')
	{
		if (limitStr.empty())
			return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters"));

		// Validate: must be a non-zero positive integer
		for (size_t i = 0; i < limitStr.size(); ++i)
		{
			if (!std::isdigit(static_cast<unsigned char>(limitStr[i])))
				return (sendError(client, IRC::ERR_INVALIDLIMIT, channelName + " l * :Invalid limit mode parameter"));
		}
		long	limit = std::strtol(limitStr.c_str(), NULL, 10);
		if (limit <= 0)
			return (sendError(client, IRC::ERR_INVALIDLIMIT, channelName + " l * :Invalid limit mode parameter"));

		channel.setUserLimit(static_cast<int>(limit));
		channel.broadcast(":" + clientNick + " MODE " + channelName + " +l " + limitStr);
	}
	else
	{
		channel.setUserLimit(std::numeric_limits<int>::max());
		channel.broadcast(":" + clientNick + " MODE " + channelName + " -l");
	}
}

// Standalone call: MODE #channel +l 10  or  MODE #channel -l
void	ModeLCommand::execute(Server &server, Client &client, const Message &msg)
{
	if (msg.params.size() < 2)
		return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters"));

	const std::string	channelName = msg.params[0];
	const std::string	modeStr = msg.params[1];
	const std::string	limitStr = (msg.params.size() > 2) ? msg.params[2] : "";

	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));
	if (!channel->getModerator(client.getFd()))
		return (sendError(client, IRC::ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator"));

	char	sign = (modeStr.size() > 0 && modeStr[0] == '-') ? '-' : '+';
	execute(client, *channel, sign, limitStr);
}
