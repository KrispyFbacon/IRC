#include "PongCommand.hpp"

void PongCommand::execute(Server& server, Client& client, const Message& msg)
{
	(void)server;
	(void)msg;
	
	std::string nickName = client.getNickname().empty() ? "*" : client.getNickname();

	Print::Ok("Received PONG from " + nickName);
}