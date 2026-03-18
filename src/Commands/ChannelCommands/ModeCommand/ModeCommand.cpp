#include "ModeCommand.hpp"
#include "Server.hpp"

// Which flags consume a positional argument?
//
//  Flag │ needs arg on '+' │ needs arg on '-'
//  ─────┼──────────────────┼─────────────────
//   i   │       no         │       no
//   t   │       no         │       no
//   k   │       yes        │       no
//   o   │       yes        │       yes
//   l   │       yes        │       no
// ─────────────────────────────────────────────────────────────────────────────

static bool	flagNeedsArg(char flag, char sign)
{
	if (flag == 'o')
		return (true);
	if (sign == '+' && (flag == 'k' || flag == 'l'))
		return (true);
	return (false);
}

std::vector<ModeCommand::ModeChange>
ModeCommand::parseModeString(const std::string &modeStr, const std::vector<std::string> &args) const
{
	std::vector<ModeChange>	changes;
	char					sign = '+';
	size_t					argIdx = 0;

	for (size_t i = 0; i < modeStr.size(); ++i)
	{
		char c = modeStr[i];

		if (c == '+' || c == '-')
		{
			sign = c;
			continue ;
		}

		ModeChange	mc;
		mc.sign = sign;
		mc.flag = c;

		if (flagNeedsArg(c, sign) && argIdx < args.size())
			mc.arg = args[argIdx++];

		changes.push_back(mc);
	}

	return (changes);
}

void	ModeCommand::execute(Server &server, Client &client, const Message &msg)
{
	if (msg.params.empty())
		return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "MODE :Not enough parameters"));

	const std::string	channelName = msg.params[0];

	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));

	// MODE #channel with no mode string → reply with current modes
	if (msg.params.size() < 2)
	{
		std::string	modeStr = "+";
		if (channel->getInviteOnly())
			modeStr += "i";
		if (channel->getTopicLocked())
			modeStr += "t";
		if (!channel->getPass().empty())
			modeStr += "k";
		if (channel->getUserLimit() != std::numeric_limits<int>::max())
		modeStr += "l";

		return (client.sendMessage(":42IRC " + IRC::RPL_CHANNELMODEIS + " " + client.getNickname() + " " + channelName + " " + modeStr));
	}

	// Only channel operators may change modes
	if (!channel->getModerator(client.getFd()))
		return (sendError(client, IRC::ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator"));

	const std::string	modeStr  = msg.params[1];
	std::vector<std::string>	modeArgs(msg.params.begin() + 2, msg.params.end());

	std::vector<ModeChange>	changes = parseModeString(modeStr, modeArgs);

	for (size_t i = 0; i < changes.size(); ++i)
	{
		const ModeChange	&mc = changes[i];

		if (mc.flag == 'i')
		{
			ModeICommand	cmd;
			cmd.execute(client, *channel, mc.sign);
		}
		else if (mc.flag == 't')
		{
			ModeTCommand	cmd;
			cmd.execute(client, *channel, mc.sign);
		}
		else if (mc.flag == 'k')
		{
			ModeKCommand	cmd;
			cmd.execute(client, *channel, mc.sign, mc.arg);
		}
		else if (mc.flag == 'o')
		{
			ModeOCommand	cmd;
			cmd.execute(server, client, *channel, mc.sign, mc.arg);
		}
		else if (mc.flag == 'l')
		{
			ModeLCommand	cmd;
			cmd.execute(client, *channel, mc.sign, mc.arg);
		}
		else
		{
			return (sendError(client, IRC::ERR_UNKNOWNMODE, std::string(1, mc.flag) + " :is unknown mode char to me"));
		}
	}
}
