#include "IRCReply.hpp"


void sendError(Client& client, const std::string& code, const std::string& msg)
{
	// Get the Client Nickname ("*" if it doesnt exist)
	std::string nickName = client.getNickname().empty() ? "*" : client.getNickname();
	
	// Build formatted IRC protocol string
	std::string fullMsg = ":" + Config::SERVER_NAME + " " + code + " " + nickName + " " + msg;
	
	client.sendMessage(fullMsg);
}


void sendReply(Client& client, const std::string& code, const std::string& msg)
{
	std::string nickName = client.getNickname().empty() ? "*" : client.getNickname();
	
	std::string fullMsg = ":" + Config::SERVER_NAME + " " + code + " " + nickName + " " + msg;
	
	client.sendMessage(fullMsg);
}