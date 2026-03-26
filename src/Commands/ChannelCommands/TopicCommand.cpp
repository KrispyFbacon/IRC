#include "TopicCommand.hpp"
#include "Server.hpp"

// command = "TOPIC"
// param[0] = "#channel"
// param[1] = "topic ..."

void	TopicCommand::execute(Server &server, Client &client, const Message &msg)
{
	Print::Debug("TOPIC Command Called!");

	if (msg.params.empty())
		return (sendError(client, IRC::ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters"));

	std::string	channelName = msg.params[0];

	// If channel exists
	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (sendError(client, IRC::ERR_NOSUCHCHANNEL, channelName + " :No such channel"));

	// Client is in the channel?
	if (!channel->getClient(client.getFd()))
		return (sendError(client, IRC::ERR_NOTONCHANNEL, channelName + " :You're not on that channel"));
	
	// No message -> view topic
	if (msg.params.size() == 1)
	{
		std::string	topic = channel->getTopic();
		if (topic.empty())
			return (sendReply(client, IRC::RPL_NOTOPIC, channelName + " :No topic is set"));
		return (sendReply(client, IRC::RPL_TOPIC, channelName + " :" + topic));
	}

	// Mode +t
	if (channel->getTopicLocked() && !channel->getModerator(client.getFd()))
		return sendError(client, IRC::ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator");

	std::string	topic = msg.params[1];
	channel->setTopic(topic);

	// Broadcast to channel
	std::string topicMsg = ":" + client.getPrefix() + " TOPIC " + channelName + " :" + topic;
	channel->broadcast(topicMsg);
}