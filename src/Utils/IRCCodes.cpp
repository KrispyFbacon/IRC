#include "IRCCodes.hpp"

namespace IRC
{
	// Registration replies
	const std::string RPL_WELCOME			= "001";
	const std::string RPL_YOURHOST			= "002";
	const std::string RPL_CREATED			= "003";
	const std::string RPL_MYINFO			= "004";

	// Channel replies
	const std::string RPL_CHANNELMODEIS		= "324";
	const std::string RPL_NOTOPIC			= "331";
	const std::string RPL_TOPIC				= "332";
	const std::string RPL_INVITING			= "341";
	const std::string RPL_NAMREPLY			= "353";
	const std::string RPL_ENDOFNAMES		= "366";

	// MOTD replies
	const std::string RPL_MOTDSTART			= "375";
	const std::string RPL_MOTD				= "372";
	const std::string RPL_ENDOFMOTD			= "376";

	// Connection errors
	const std::string ERR_NOSUCHNICK		= "401";
	const std::string ERR_NOSUCHCHANNEL		= "403";
	const std::string ERR_CANNOTSENDTOCHAN	= "404";
	const std::string ERR_UNKNOWNCOMMAND	= "421";
	const std::string ERR_NOMOTD			= "422";

	// Nickname errors
	const std::string ERR_NONICKNAMEGIVEN	= "431";
	const std::string ERR_ERRONEUSNICKNAME	= "432";
	const std::string ERR_NICKNAMEINUSE		= "433";

	// Channel membership errors
	const std::string ERR_USERNOTINCHANNEL	= "441";
	const std::string ERR_NOTONCHANNEL		= "442";
	const std::string ERR_USERONCHANNEL		= "443";

	// Authentication errors
	const std::string ERR_NOTREGISTERED		= "451";
	const std::string ERR_NEEDMOREPARAMS	= "461";
	const std::string ERR_ALREADYREGISTRED	= "462";
	const std::string ERR_PASSWDMISMATCH	= "464";

	// Channel operator errors
	const std::string ERR_CHANNELISFULL		= "471";
	const std::string ERR_INVITEONLYCHAN	= "473";
	const std::string ERR_BADCHANNELKEY		= "475";
	const std::string ERR_CHANOPRIVSNEEDED	= "482";

	// MODE errors
	const std::string ERR_UNKNOWNMODE		= "472";
	const std::string ERR_KEYSET			= "467";
	const std::string ERR_INVALIDLIMIT		= "696";
}

