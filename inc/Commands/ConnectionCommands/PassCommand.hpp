#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class PassCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new PassCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif