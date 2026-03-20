#ifndef PRIVMSGCOMMAND_HPP
#define PRIVMSGCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class PrivmsgCommand : public ACommand
{
	private:
		void handleChannelMessage(Server& , Client&, const std::string&, const std::string& );
		void handlePrivateMessage(Server& , Client&, const std::string&, const std::string& );

	public:
		static ACommand* make() { return new PrivmsgCommand(); }

		void execute(Server& server, Client& client, const Message& msg);
};

#endif