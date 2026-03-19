#ifndef MODELCOMMAND_HPP
#define MODELCOMMAND_HPP
 
#include "ACommand.hpp"
 
class Server;
class Client;
class Channel;
 
class ModeLCommand : public ACommand
{
	public:
		static ACommand *make() { return new ModeLCommand(); }
 
		void execute(Server &server, Client &client, const Message &msg);
 
		void execute(Client &client, Channel &channel, char sign, const std::string &limit);
};
 
#endif