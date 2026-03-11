#include "KickParsing.hpp"

void	parseKickParams(const Message &msg, std::string &targetNick, std::string &reason)
{
	std::string	raw = msg.message;
	size_t	space = raw.find(' ');

	targetNick = raw.substr(0, space);

	if (space != std::string::npos)
	{
		reason = raw.substr(space + 1);
		if (!reason.empty() && reason[0] == ':')
			reason = reason.substr(1);
	}
	else
		reason = "No reason given";
}