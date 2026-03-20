#include "PrivmsgCommand.hpp"
#include "Server.hpp"

void NickCommand::execute(Server& server, Client& client, const Message& msg)
{
	Print::Debug ("PRIVMSG Command Called!");

	// Check for target and message paremeters
	if (msg.params.empty() < 2)
	{
		if (msg.params.size() < 1 || msg.params[0].empty())
			return (sendError(client, IRC::ERR_NORECIPIENT, ":No recipient given (PRIVMSG)"));
		else
			return (sendError(client, IRC::ERR_NOTEXTTOSEND, ":No text to send"));
	}

	std::string target = msg.params[0];
	std::string text = msg.params[1];

	argumentSplit	jm = splitParse(msg);

	// for (size_t i = 0; i < jm.channels.size(); ++i)
	{
		if (jm.channels[i] == '#' || jm.channels[i] == '&')
			handleChannelMessage(server, client, jm.channels[i], jm.keys[0]);
		else
			handlePrivateMessage(server, client, jm.channels[i], jm.keys[0]);
	}
		//handleOneJoin(server, client, jm.channels[i], jm.keys[0]); //TODO or leave jm.keys[i]?
}



/* ================================= PRIVATE =============================== */

void PrivmsgCommand::handleChannelMessage(Server& server, Client& client, const std::string& channelName, const std::string& msg)
{
	// Check if channel exists
	Channel* channel = server.getChannel(channelName);
	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + ":No such channel"));

	// Check if sender is in the channel
	if (!channel->getClient(client.getFd()))
		return(sendError(client, IRC::ERR_CANNOTSENDTOCHAN, channelName + " :Cannot send to channel"));

	// TODO Broadcast to everyone in the channel EXCEPT the sender
	std::string broadcastMsg = ":" + client.getPrefix() + " PRIVMSG " + channelName + " :" + msg;
	// TODO Having 2 types of broadcast? JUST PRIVMSG has ignores itself on broadcast
		//channel->broadcast(broadcastMsg, client.getFd());
	
	Print::Ok("Broadcasted message from " NUM_COLOR + client.getNickname() + RST + " to " + NUM_COLOR + channelName);
}

void PrivmsgCommand::handlePrivateMessage(Server& server, Client& sender, const std::string& targetNick, const std::string& msg)
{
	// Check if target exists
	Client* target = server.getClientByNickname(targetNick);
	if (!target)
		return (sendError(sender, IRC::ERR_NOSUCHNICK, targetNick + " :No such channel"));
	
	// Send the message!
	std::string dmMsg = ":" + sender.getPrefix() + " PRIVMSG " + targetNick + " :" + msg;
	target->sendMessage(dmMsg);
	

	Print::Ok("DM from " NUM_COLOR + sender.getNickname() + RST + " to " + NUM_COLOR + targetNick);
}

