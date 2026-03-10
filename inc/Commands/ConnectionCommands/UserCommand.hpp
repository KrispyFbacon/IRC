#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class UserCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new UserCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif