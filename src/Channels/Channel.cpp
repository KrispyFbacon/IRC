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

std::string	Channel::getChannelName() const
{
	return(_name);
}

std::string	channel::getTopic() const
{
	return (_topic);
}

void	channel::setTopic(const std::string topic)
{
	_topic = topic;
}

Client	*Channel::getModerator(int clientFd)
{
	std::map<int, Client*>::iterator it = _moderators.find(clientFd);

	if (it == _moderators.end())
		return (NULL);

	return (it->second);
}

bool	Channel::addModerator(Client *client)
{
	int	fd = client->getFd();

	if (_moderators.find(fd) != _moderators.end())
		return (false);

	_moderators.insert(std::make_pair(fd, client));
	return (true);
}

bool	Channel::removeModerator(Client *client)
{
	int	fd = client->getFd();

	std::map<int, Client*>::iterator	it = _moderators.find(fd);
	if (it == _moderators.end())
		return (false);

	_moderators.erase(fd);

	return (true);
}

bool	Channel::addClient(Client *client)
{
	int	fd = client->getFd();

	if (_clients.find(fd) != _clients.end())
		return (false);

	_clients.insert(std::make_pair(fd, client));
	return (true);
}

bool	Channel::removeClient(Client *client)
{
	int	fd = client->getFd();

	std::map<int, Client*>::iterator	it = _clients.find(fd);
	if (it == _clients.end())
		return (false);

	_clients.erase(it);

	return (true);
}
