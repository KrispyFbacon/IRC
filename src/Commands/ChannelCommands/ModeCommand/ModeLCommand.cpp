#include "ModeLCommand.hpp"
#include "Server.hpp"

// Direct call from ModeCommand with pre-parsed sign and limit string
void	ModeLCommand::execute(Client &client, Channel &channel, char sign, const std::string &limitStr)
{
	const std::string	channelName = channel.getChannelName();
	const std::string	clientNick = client.getNickname();

	if (sign == '+')
	{
		if (limitStr.empty())
		{
			sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
			return ;
		}

		// Validate: must be a non-zero positive integer
		for (size_t i = 0; i < limitStr.size(); ++i)
		{
			if (!std::isdigit(static_cast<unsigned char>(limitStr[i])))
			{
				sendError(client, IRC::ERR_INVALIDLIMIT, channelName + " l * :Invalid limit mode parameter");
				return ;
			}
		}
		long	limit = std::strtol(limitStr.c_str(), NULL, 10);
		if (limit <= 0)
		{
			sendError(client, IRC::ERR_INVALIDLIMIT, channelName + " l * :Invalid limit mode parameter");
			return ;
		}

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
	{
		sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
		return ;
	}

	const std::string	channelName = msg.params[0];
	const std::string	modeStr = msg.params[1];
	const std::string	limitStr = (msg.params.size() > 2) ? msg.params[2] : "";

	Channel	*channel = server.getChannel(channelName);
	if (!channel)
	{
		sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel");
		return ;
	}
	if (!channel->getModerator(client.getFd()))
	{
		sendError(client, IRC::ERR_CHANOPRIVSNEEDED,
				  channelName + " :You're not channel operator");
		return ;
	}

	char	sign = (modeStr.size() > 0 && modeStr[0] == '-') ? '-' : '+';
	execute(client, *channel, sign, limitStr);
}
