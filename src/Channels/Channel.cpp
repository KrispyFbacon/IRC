#include "Channel.hpp"

Channel::Channel(std::string name) : _name(name), _topic(""){}

Channel::Channel(std::string name, const Channel &other) : _name(name)
{
	copyChannelInfo(*this, other);
}

Channel::~Channel()
{
	_clients.clear();
}

void	Channel::copyChannelInfo(Channel &dest, const Channel &src)
{
	dest._topic = src._topic;
	dest._clients = src._clients;
}