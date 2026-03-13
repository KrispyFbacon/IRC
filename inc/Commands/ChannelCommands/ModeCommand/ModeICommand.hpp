#ifndef MODEICOMMAND_HPP
#define MODEICOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class ModeICommand : public ACommand
{
	private:

	public:
		static ACommand *make() { return new ModeICommand(); }

		void execute(Server &server, Client &client, const Message &msg);
};

#endif