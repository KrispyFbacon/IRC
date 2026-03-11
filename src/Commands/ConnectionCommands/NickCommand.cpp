#include "NickCommand.hpp"

void NickCommand::execute(Server& server, Client& client, const Message& msg)
{
	(void)server;
	Print::Debug ("NICK Command Called!");

	if (msg.params.empty()) // msg.param [0]
	{
		sendError(client, IRC::ERR_NEEDMOREPARAMS, "NICK :Not enough parameters");
		return;
	}

	//TODO ERR_NONICKNAMEGIVEN	ERR_ERRONEUSNICKNAME
	//ERR_NICKNAMEINUSE	ERR_NICKCOLLISION
	// TODO: Check if newNick is already in use by looping through server._clients!
	// if (isTaken) { sendError 433; return; }
	
	// TODO std::string oldNick = client.getNickname();
	
	// TODO : Cant be changed if not registed
	// if (client.isRegistered()) {
	// 	// Build the broadcast message
	// 	std::string broadcast = ":" + oldNick + "!" + client.getUsername() + Config::SERVERNAME + " NICK :" + newNick;
		
	// 	// TODO: Send this broadcast to the client AND everyone in their channels
	//  // TODO DO BRODCAST
	// 	client.sendMessage(broadcast);
	// }
	

	client.setNickname(msg.target); // msg.param[0]?;

}

// TODO CHECK REGISTRATION
// //void checkRegistration(Client& client)
// {
// 	// If they are already registered, do nothing
// 	if (client.isRegistered())
// 		return;

// 	// Check if they have finished all the required steps
// 	bool hasPassword = client.isAuthenticated(); // (Set to true by PassCommand)
// 	bool hasNickname = !client.getNickname().empty(); // (Set by NickCommand)
// 	bool hasUsername = !client.getUsername().empty(); // (Set by UserCommand)

// 	// Are all three complete?
// 	if (hasPassword && hasNickname && hasUsername)
// 	{
// 		// Success! Lock them in.
// 		client.setRegistered(true);

// 		// Send the 4 "mandatory" welcome replies
// 		sendReply(client, IRC::RPL_WELCOME, ":Welcome to the Internet Relay Network " + client.getNickname());
// 		sendReply(client, IRC::RPL_YOURHOST, ":Your host is " + Config::SERVER_NAME + ", running version 1.0");
// 		sendReply(client, IRC::RPL_CREATED, ":This server was created today");
// 		sendReply(client, IRC::RPL_MYINFO, ":" + Config::SERVER_NAME + " 1.0 o o");
		
// 		// (Optional: Send MOTD here if you implement it)
// 	}
// }