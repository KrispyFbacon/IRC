#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class NickCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new NickCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif