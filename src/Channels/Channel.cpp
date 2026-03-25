#include "Channel.hpp"

Channel::Channel(std::string name): _name(name), _pass(""), _topic(""), _userLimit(std::numeric_limits<int>::max()), _oldestInvited(0), _numberOfInvited(0), _inviteOnly(false), _topicLocked(false){}

Channel::Channel(std::string name, const Channel &other) : _name(name)
{
	copyChannelInfo(*this, other);
}

Channel::~Channel()
{
	_clients.clear();
	_moderators.clear();
	_invited.clear();
	_joinOrder.clear();
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
	std::map<int, Client*>::iterator modIt = _moderators.find(clientFd);

	if (modIt == _moderators.end())
		return false; 

	_moderators.erase(modIt);

	for (size_t i = 0; i < _joinOrder.size(); ++i)


	if (_moderators.empty() && !_joinOrder.empty())
		return(promoteToModerator(clientFd));

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

	client.addChannel(*(this));
	_joinOrder.push_back(fd);

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
	std::map<int, Client*>::iterator	cliIt = _clients.find(clientFd);

	if (cliIt == _clients.end())
		return (false);

	removeModerator(cliIt->first);
	_clients.erase(cliIt);

	// Remove from the chronological succession list
	std::vector<int>::iterator joinIt = std::find(_joinOrder.begin(), _joinOrder.end(), clientFd);
	if (joinIt != _joinOrder.end())
		_joinOrder.erase(joinIt);

	return (true);
}

bool	Channel::addInvited(const std::string client)
{
	if (_numberOfInvited < Config::MAX_INVITED)
	{
		_invited.push_back(client);
		_numberOfInvited++;
	}
	else
	{
		_invited[_oldestInvited] = client;
		_oldestInvited = (_oldestInvited + 1) % Config::MAX_INVITED;
	}
	return (true);
}

std::string	Channel::getInvited(const std::string client) const
{
	for (size_t i = 0; i < _invited.size(); ++i)
	{
		if (_invited[i] == client)
				return (client);
	}

	return ("");
}


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


/* ================================= PRIVATE =============================== */

bool	Channel::promoteToModerator(int ignoreFd)
{
	for (size_t i = 0; i < _joinOrder.size(); ++i)
	{
		int	oldestFd = _joinOrder[i];

		if (oldestFd == ignoreFd)
			continue ;

		std::map<int, Client*>::iterator it = _clients.find(oldestFd);
		if (it == _clients.end())
			continue ; // user no longer in channel

		Client* newMod = it->second;
		if (!newMod)
			continue ;

		addModerator(*newMod);

		std::string modeMsg = ":" + Config::SERVER_NAME + " MODE " + _name + " +o " + newMod->getNickname();
		broadcast(modeMsg);

		Print::Ok("Server promoted " + newMod->getNickname() + " to operator status in " + _name);
		return (true);
	}

	return (false);
}
