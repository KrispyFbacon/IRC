#include "ModeICommand.hpp"

// Direct call from ModeCommand with pre-parsed sign
void	ModeICommand::execute(Client &client, Channel &channel, char sign)
{
	channel.setInviteOnly(sign == '+');

	std::string	modeMsg = ":" + client.getNickname() + " MODE " + channel.getChannelName() + " " + sign + "i";
	channel.broadcast(modeMsg);
}

// Standalone call: MODE #channel +i  or  MODE #channel -i
void	ModeICommand::execute(Server &server, Client &client, const Message &msg)
{
	(void)server;

	if (msg.params.size() < 2)
	{
		sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
		return ;
	}

	const std::string	channelName = msg.params[0];
	const std::string	modeStr = msg.params[1];

	Channel	*channel = server.getChannel(channelName);
	if (!channel)
	{
		sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel");
		return ;
	}
	if (!channel->getModerator(client.getFd()))
	{
		sendError(client, IRC::ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator");
		return ;
	}

	char	sign = (modeStr.size() > 0 && modeStr[0] == '-') ? '-' : '+';
	execute(client, *channel, sign);
}
