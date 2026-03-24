#include "Channel.hpp"

Channel::Channel(std::string name): _name(name), _pass(""), _topic(""), _userLimit(std::numeric_limits<int>::max()), _oldestInvited(0), _numberOfInvited(0), _inviteOnly(false), _topicLocked(false){}

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
	dest._numberOfInvited = dest._numberOfInvited;
	dest._oldestInvited = src._oldestInvited;
}

const std::map<int, Client*>	&Channel::getClients() const
{
	return (_clients);
}

const std::map<int, Client*>	&Channel::getModerators() const
{
	return (_moderators);
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

	const std::string clientNickname = client.getNickname();
	removeInvited(clientNickname);
	
	_clients[fd] = &client;

	Channel	&channelRef = (*this);
	client.addChannel(channelRef);

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

bool	Channel::addInvited(const std::string client)
{
	if(_numberOfInvited < Config::MAX_INVITED)
	{
		_invited[_numberOfInvited] = client;
		_numberOfInvited++;
		return (true);
	}
	else
	{
		_invited[_oldestInvited] = client;
		_oldestInvited = (_oldestInvited + 1) % Config::MAX_INVITED;
		return (true);
	}
	
}

std::string	Channel::getInvited(const std::string client) const
{
	for (size_t i = 0; i < _invited.size(); ++i)
	{
		if (_invited[i] == client)
				return (client);
	}

	return (NULL);
}

// TODO
bool	Channel::removeInvited(const std::string client)
{
	for (size_t i = 0; i < _invited.size(); ++i)
	{
		if (_invited[i] == client)
		{
			_invited.erase(_invited.begin() + i);
			return (true);
		}
	}

	return (false);
}

void	Channel::broadcast(const std::string &msg, int excludeFd)
{
	std::map<int, Client*>::iterator it = _clients.begin();

	for (; it != _clients.end(); ++it)
	{
		if (it->first == excludeFd)
			continue;

		it->second->sendMessage(msg);
	}
}
