#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "Utils.hpp"
#include "Client.hpp"

#include "Parsing.hpp"
//#include "Message.hpp"

#include "ACommand.hpp"
#include "JoinCommand.hpp"
#include "KickCommand.hpp"
#include "TopicCommand.hpp"
#include "InviteCommand.hpp"

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