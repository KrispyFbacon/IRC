#ifndef MODEOCOMMAND_HPP
#define MODEOCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;
class Channel;

class ModeOCommand : public ACommand
{
	public:
		static ACommand *make() { return new ModeOCommand(); }

		void execute(Server &server, Client &client, const Message &msg);

		// Called directly by ModeCommand with pre-parsed args
		void execute(Server &server, Client &client, Channel &channel,
					 char sign, const std::string &targetNick);
};

#endif
