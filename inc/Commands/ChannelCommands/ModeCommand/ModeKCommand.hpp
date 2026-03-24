#ifndef MODEKCOMMAND_HPP
#define MODEKCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;
class Channel;

class ModeKCommand : public ACommand
{
	public:
		static ACommand *make() { return new ModeKCommand(); }

		void execute(Server &server, Client &client, const Message &msg);

		// Called directly by ModeCommand with pre-parsed args
		void execute(Client &client, Channel &channel, char sign, const std::string &key);
};

#endif
