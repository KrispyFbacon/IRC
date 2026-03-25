#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "Utils.hpp"
#include "Client.hpp"

#include "Parsing.hpp"
#include "IRCReply.hpp"

#include "ACommand.hpp"
#include "NickCommand.hpp"
#include "PassCommand.hpp"
#include "PingCommand.hpp"
#include "PongCommand.hpp"
#include "QuitCommand.hpp"
#include "UserCommand.hpp"
#include "PartCommand.hpp"

#include "JoinCommand.hpp"
#include "KickCommand.hpp"
#include "TopicCommand.hpp"
#include "InviteCommand.hpp"
#include "ModeCommand.hpp"
#include "ModeICommand.hpp"
#include "ModeKCommand.hpp"
#include "ModeLCommand.hpp"
#include "ModeOCommand.hpp"
#include "ModeTCommand.hpp"

#include "PrivmsgCommand.hpp"

class Server;
class Client;


class CommandFactory
{
	private:
		typedef	ACommand* (*Creator)(void);
		typedef	std::map<std::string, Creator> CommandMap;
		typedef	CommandMap::iterator CommandIt;

		CommandMap	_commands; // map with all commands options

	public:
		CommandFactory();
		~CommandFactory();

		void	execute(Server& server, Client& client, const Message& msg);
	};

#endif