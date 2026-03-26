#ifndef PARTCOMMAND_HPP
#define PARTCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class PartCommand : public ACommand
{
	private:

	public:
		static ACommand* make() { return new PartCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif