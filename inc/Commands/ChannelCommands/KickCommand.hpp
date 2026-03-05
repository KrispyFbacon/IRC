#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class KickCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new KickCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif