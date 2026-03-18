#include "ModeOCommand.hpp"
#include "Server.hpp"

// Direct call from ModeCommand with pre-parsed sign and target nick
void	ModeOCommand::execute(Server &server, Client &client, Channel &channel, char sign, const std::string &targetNick)
{
	const std::string	channelName = channel.getChannelName();
	const std::string	clientNick = client.getNickname();

	if (targetNick.empty())
	{
		sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
		return ;
	}

	Client	*target = server.getClientByNickname(targetNick);
	if (!target)
	{
		sendError(client, IRC::ERR_NOSUCHNICK, targetNick + " :No such nick");
		return ;
	}
	if (!channel.getClient(target->getFd()))
	{
		sendError(client, IRC::ERR_USERNOTINCHANNEL,
				  targetNick + " " + channelName + " :They aren't on that channel");
		return ;
	}

	if (sign == '+')
		channel.addModerator(*target);
	else if (channel.getModerator(target->getFd()))
		channel.removeModerator(target->getFd());

	channel.broadcast(":" + clientNick + " MODE " + channelName + " " + sign + "o " + targetNick);
}

// Standalone call: MODE #channel +o nick  or  MODE #channel -o nick
void	ModeOCommand::execute(Server &server, Client &client, const Message &msg)
{
	if (msg.params.size() < 3)
	{
		sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
		return ;
	}

	const std::string	channelName = msg.params[0];
	const std::string	modeStr = msg.params[1];
	const std::string	targetNick = msg.params[2];

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
	execute(server, client, *channel, sign, targetNick);
}
