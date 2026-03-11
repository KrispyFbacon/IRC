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

std::string	Channel::getTopic() const
{
	return (_topic);
}

void	Channel::setTopic(const std::string topic)
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

Client	*Channel::getClient(int clientFd)
{
	std::map<int, Client*>::iterator it = _clients.find(clientFd);

	if (it == _clients.end())
		return (NULL);

	return (it->second);
}

Client	*Channel::getClientByNickname(const std::string nick)
{
	std::map<int, Client*>::iterator it = _clients.begin();

	for (; it != _clients.end(); ++it)
	{
		Client	*client = it->second;

		if (client->getNickname() == nick)
			return (it->second);
	}
	return (NULL);
}

bool	Channel::addModerator(Client &client)
{
	int	fd = client.getFd();

	if (_moderators.find(fd) != _moderators.end())
		return (false);

	_moderators[fd] = &client;
	return (true);
}

bool	Channel::removeModerator(const int clientFd)
{
	std::map<int, Client*>::iterator	it = _moderators.find(clientFd);
	if (it == _moderators.end())
		return (false);

	_moderators.erase(it);

	return (true);
}

bool	Channel::addClient(Client &client)
{
	int	fd = client.getFd();

	if (_clients.find(fd) != _clients.end())
		return (false);

	_clients[fd] = &client;
	return (true);
}

bool	Channel::removeClient(const int clientFd)
{
	std::map<int, Client*>::iterator	it = _clients.find(clientFd);
	if (it == _clients.end())
		return (false);

	_clients.erase(it);

	return (true);
}

void	Channel::broadcast(const std::string msg)
{
	std::map<int, Client*>::iterator it = _clients.begin();

	for (; it != _clients.end(); ++it)
	{
		Client	*client = it->second;
		std::string	clientName = client->getNickname();

		client->sendMessage(msg);
	}
}
