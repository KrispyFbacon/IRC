#ifndef MODEICOMMAND_HPP
#define MODEICOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;
class Channel;

class ModeICommand : public ACommand
{
	public:
		static ACommand *make() { return new ModeICommand(); }

		void execute(Server &server, Client &client, const Message &msg);

		// Called directly by ModeCommand with pre-parsed args
		void execute(Client &client, Channel &channel, char sign);
};

#endif
