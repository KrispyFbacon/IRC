#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "Utils.hpp"
#include "ACommand.hpp"
#include "Parsing.hpp"
//#include "Message.hpp"

class Server;
class Client;

class JoinCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new JoinCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

void execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("THIS IS JOIN COMMAND");
}

#endif