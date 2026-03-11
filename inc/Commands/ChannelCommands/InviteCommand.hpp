#ifndef INVITECOMMAND_HPP
#define INVITECOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class InviteCommand : public ACommand
{
	private:

	public:
		static ACommand *make() { return new InviteCommand(); }

		void execute(Server &server, Client &client, const Message &msg);
};

#endif