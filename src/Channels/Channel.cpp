#include "Channel.hpp"

Channel::Channel(std::string name): _name(name), _pass(""), _topic(""), _userLimit(std::numeric_limits<int>::max()){}

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
	dest._pass = src._pass;
	dest._topic = src._topic;
	dest._clients = src._clients;
	dest._moderators = src._moderators;
	dest._userLimit = src._userLimit;
	dest._inviteOnly = src._inviteOnly;
	dest._topicLocked = src._topicLocked;
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

std::string	Channel::getPass() const
{
	return (_pass);
}

void	Channel::setPass(const std::string pass)
{
	if (isValidPassword(pass))
		_pass = pass;
}

int	Channel::getUserLimit() const
{
	return (_userLimit);
}

void	Channel::setUserLimit(const int userLimit)
{
	if (userLimit > 0 && userLimit < std::numeric_limits<int>::max())
		_userLimit = userLimit;
}

bool	Channel::getInviteOnly() const
{
	return (_inviteOnly);
}

void	Channel::setInviteOnly(bool option)
{
	_inviteOnly = option;
}

bool	Channel::getTopicLocked() const
{
	return (_topicLocked);
}

void	Channel::setTopicLocked(bool option)
{
	_topicLocked = option;
}

bool	Channel::addModerator(Client &client)
{
	int	fd = client.getFd();

	if (_moderators.find(fd) != _moderators.end())
		return (false);

	_moderators[fd] = &client;
	return (true);
}

Client	*Channel::getModerator(int clientFd)
{
	std::map<int, Client*>::iterator it = _moderators.find(clientFd);

	if (it == _moderators.end())
		return (NULL);

	return (it->second);
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

	if (_invited.find(fd) != _invited.end())
		removeInvited(fd);
	
	_clients[fd] = &client;
	return (true);
}

Client	*Channel::getClient(const int clientFd)
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

bool	Channel::removeClient(const int clientFd)
{
	std::map<int, Client*>::iterator	it = _clients.find(clientFd);
	if (it == _clients.end())
		return (false);

	_clients.erase(it);

	return (true);
}

bool	Channel::addInvited(Client &client)
{
	int	fd = client.getFd();

	if (_clients.find(fd) != _invited.end())
		return (false);

	_invited[fd] = &client;
	return (true);
}

Client	*Channel::getInvited(int clientFd)
{
	std::map<int, Client*>::iterator it = _invited.find(clientFd);

	if (it == _invited.end())
		return (NULL);

	return (it->second);
}

Client	*Channel::getInvitedByNickname(const std::string nick)
{
	std::map<int, Client*>::iterator it = _invited.begin();

	for (; it != _invited.end(); ++it)
	{
		Client	*client = it->second;

		if (client->getNickname() == nick)
			return (it->second);
	}
	return (NULL);
}

bool	Channel::removeInvited(const int clientFd)
{
	std::map<int, Client*>::iterator	it = _invited.find(clientFd);
	if (it == _invited.end())
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
