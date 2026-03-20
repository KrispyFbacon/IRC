#ifndef PRIVMSGCOMMAND_HPP
#define PRIVMSGCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class PrivmsgCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new PrivmsgCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif