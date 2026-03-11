#ifndef PONGCOMMAND_HPP
#define PONGCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class PongCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new PongCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif