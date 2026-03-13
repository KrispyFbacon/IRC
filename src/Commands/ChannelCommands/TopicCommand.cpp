#include "TopicCommand.hpp"

// command = "KICK"
// param[0] = "#channel"
// param[1] = "topic ..."

void	TopicCommand::execute(Server &server, Client &client, const Message &msg)
{
	std::string	channelName = msg.params[0];
	std::string	topic = msg.params[1];

	// If channel exists
	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (client.sendMessage(":42IRC 403 " + client.getNickname() + " " + channelName + " :No such channel"));

	// Client is in the channel?
	if (!channel->getClient(client.getFd()))
		return (client.sendMessage(":42IRC 442 " + client.getNickname() + " " + channelName + " :You're not on that channel"));

	// No message -> view topic
	if (topic.empty())
	{
		std::string	topic = channel->getTopic();
		if (topic.empty())
			return (client.sendMessage(":42IRC 331 " + client.getNickname() + " " + channelName + " :No topic is set"));
		return (client.sendMessage(":42IRC 332 " + client.getNickname() + " " + channelName + " :" + topic));
	}

	channel->setTopic(topic);

	// Broadcast to channel
	std::string	topicMsg = ":" + client.getNickname() + " TOPIC " + channelName + " :" + topic;
	channel->broadcast(topicMsg);
}