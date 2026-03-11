#ifndef TOPICCOMMAND_HPP
#define TOPICCOMMAND_HPP

#include "ACommand.hpp"

class Server;
class Client;

class TopicCommand : public ACommand
{
	private:

	public:
		static ACommand *make() { return new TopicCommand(); }

		void execute(Server &server, Client &client, const Message &msg);
};

#endif