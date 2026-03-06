#ifndef PingCommand_HPP
#define PingCommand_HPP

#include "ACommand.hpp"

class Server;
class Client;

class PingCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new PingCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif