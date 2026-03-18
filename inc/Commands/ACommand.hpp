#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include "Utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#include "Parsing.hpp"
#include "IRCReply.hpp"
//#include "Message.hpp"

class Server;
class Client;

class ACommand
{
	private:

	public:
		ACommand() {}
		virtual ~ACommand() {}

		virtual void execute(Server& server, Client& client, const Message& msg) = 0;
};

#include "Server.hpp"

#endif