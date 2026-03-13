#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class QuitCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new QuitCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif