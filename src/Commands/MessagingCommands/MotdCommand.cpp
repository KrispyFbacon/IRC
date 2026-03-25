#include "MotdCommand.hpp"
#include "Server.hpp"

void MotdCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug("MOTD Command Called!");

	(void)server;
	(void)msg;

	std::ifstream file("motd.txt");
	std::string line;

	if (!file.is_open())
	{
		client.sendMessage(":" + Config::SERVER_NAME + " " + IRC::ERR_NOMOTD + " " +
			client.getNickname() + " :MOTD File is missing");
		return ;
	}

	// Start of MOTD
	client.sendMessage(":" + Config::SERVER_NAME + " " + IRC::RPL_MOTDSTART + " " +
		client.getNickname() + " :- " + Config::SERVER_NAME + " Message of the Day -");

	while (std::getline(file, line))
	{
		client.sendMessage(":" + Config::SERVER_NAME + " " + IRC::RPL_MOTD + " " +
			client.getNickname() + " :- " + line);
	}

	// End of MOTD
	client.sendMessage(":" + Config::SERVER_NAME + " " + IRC::RPL_ENDOFMOTD + " " +
		client.getNickname() + " :End of MOTD command");
}