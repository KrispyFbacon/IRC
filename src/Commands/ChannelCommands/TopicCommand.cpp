#include "TopicCommand.hpp"

// command = "KICK"
// target  = "#channel"
// message = "nick :reason"

void	TopicCommand::execute(Server &server, Client &client, const Message &msg)
{
	std::string	channelName = msg.target;

	// If channel exists
	Channel	*channel = server.getChannel(channelName);
	if (!channel)
		return (client.sendMessage(":42IRC 403 " + client.getNickname() + " " + channelName + " :No such channel"));

	// Client is in the channel?
	if (!channel->hasClient(client.getFd()))
		return (client.sendMessage(":42IRC 442 " + client.getNickname() + " " + channelName + " :You're not on that channel"));

	// No message -> view topic
	if (msg.message.empty())
	{
		std::string	topic = channel->getTopic();
		if (topic.empty())
			return (client.sendMessage(":42IRC 331 " + client.getNickname() + " " + channelName + " :No topic is set"));
		return (client.sendMessage(":42IRC 332 " + client.getNickname() + " " + channelName + " :" + topic));
	}

	// Set new topic (strip leading ':')
	std::string	newTopic = msg.message;
	if (!newTopic.empty() && newTopic[0] == ':')
		newTopic = newTopic.substr(1);

	channel->setTopic(newTopic);

	// Broadcast to channel
	std::string	topicMsg = ":" + client.getNickname() + " TOPIC " + channelName + " :" + newTopic;
	channel->broadcast(topicMsg);
}