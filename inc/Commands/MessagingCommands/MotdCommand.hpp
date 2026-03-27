#ifndef MOTDCOMMAND_HPP
#define MOTDCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class MotdCommand : public ACommand
{
	private:

	public:
		static ACommand *make() { return new MotdCommand(); }

		void execute(Server &server, Client &client, const Message &msg);
};

#endif