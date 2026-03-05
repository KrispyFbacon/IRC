#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class JoinCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new JoinCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif