#ifndef IRCCODES_HPP
#define IRCCODES_HPP

#include <string>

namespace IRC
{
	// Registration replies
	extern const std::string RPL_WELCOME;
	extern const std::string RPL_YOURHOST;
	extern const std::string RPL_CREATED;
	extern const std::string RPL_MYINFO;

	// Channel replies
	extern const std::string RPL_CHANNELMODEIS;
	extern const std::string RPL_NOTOPIC;
	extern const std::string RPL_TOPIC;
	extern const std::string RPL_INVITING;
	extern const std::string RPL_NAMREPLY;
	extern const std::string RPL_ENDOFNAMES;

	// MOTD replies
	extern const std::string RPL_MOTDSTART;
	extern const std::string RPL_MOTD;
	extern const std::string RPL_ENDOFMOTD;

	// Connection errors
	extern const std::string ERR_NOSUCHNICK;
	extern const std::string ERR_NOSUCHCHANNEL;
	extern const std::string ERR_CANNOTSENDTOCHAN;
	extern const std::string ERR_UNKNOWNCOMMAND;
	extern const std::string ERR_NOMOTD;

	// Nickname errors
	extern const std::string ERR_NONICKNAMEGIVEN;
	extern const std::string ERR_ERRONEUSNICKNAME;
	extern const std::string ERR_NICKNAMEINUSE;

	// Channel membership errors
	extern const std::string ERR_USERNOTINCHANNEL;
	extern const std::string ERR_NOTONCHANNEL;
	extern const std::string ERR_USERONCHANNEL;

	// Authentication errors
	extern const std::string ERR_NOTREGISTERED;
	extern const std::string ERR_NEEDMOREPARAMS;
	extern const std::string ERR_ALREADYREGISTRED;
	extern const std::string ERR_PASSWDMISMATCH;

	// Channel operator errors
	extern const std::string ERR_CHANNELISFULL;
	extern const std::string ERR_INVITEONLYCHAN;
	extern const std::string ERR_BADCHANNELKEY;
	extern const std::string ERR_CHANOPRIVSNEEDED;

	// MODE errors
	extern const std::string ERR_UNKNOWNMODE;
	extern const std::string ERR_KEYSET;
	extern const std::string ERR_INVALIDLIMIT;
}

#endif