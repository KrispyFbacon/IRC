#include "Client.hpp"

Client::Client(int fd) 
		: _fd(fd), _isRegistered(false), _isAuthenticated(false), 
			_isDisconnected(false) {}

Client::~Client()
{
	_channels.clear();
}

// Getters

int	Client::getFd() const
{
	return (_fd);
}

bool	Client::isRegistered() const
{
	return (_isRegistered);
}

bool	Client::isAuthenticated() const
{
	return (_isAuthenticated);
}

bool Client::isDisconnected() const
{ 
	return (_isDisconnected);
}

std::string	Client::getUsername() const
{
	return (_username);
}

std::string	Client::getPassword() const
{
	return (_password);
}

std::string	Client::getNickname() const
{
	return (_nickname);
}


std::string	Client::getPrefix() const
{
	return (_nickname + "!" + _username + "@localhost");
}


// Setters

void	Client::setUsername(std::string username)
{
	_username = username;
}

void	Client::setPassword(std::string password)
{
	_password = password;
}

void	Client::setNickname(std::string nickname)
{
	_nickname = nickname;
}


void	Client::setRegistered(bool isRegistered)
{
	_isRegistered = isRegistered;
}

void	Client::setAuthenticated(bool isAuthenticated)
{
	_isAuthenticated = isAuthenticated;
}

void	Client::setDisconnected(bool status)
{
	_isDisconnected = status;
}

std::string	&Client::getBuffer()
{
	return (_buffer);
}

size_t	Client::getBufferSize() const
{
	return (_buffer.size());
};

void	Client::appendBuffer(const char *data, size_t len)
{
	_buffer.append(data, len);
};

bool	Client::getNextMessage(std::string &msg)
{
	size_t	pos = _buffer.find("\r\n");
	if (pos == std::string::npos)
		return (false);

	msg = _buffer.substr(0, pos);
	_buffer.erase(0, pos + 2);

	return (true);
};

void	Client::clearBuffer()
{
	std::string().swap(_buffer);
};

void	Client::addChannel(Channel &channel)
{
	_channels[channel.getChannelName()] = &channel;
}

void	Client::addChannel(Channel &channel)
{
	_channels[channel.getChannelName()] = &channel;
}

void	Client::removeChannel(const std::string &str)
{
	_channels.erase(str);
}

void	Client::sendMessage(const std::string& msg)
{
	std::string line = msg + "\r\n";
	send(_fd, line.c_str(), line.size(), 0);
}

void	Client::broadcast(const std::string& msg)
{
	// Clients that already recieved message
	std::vector<int> notifiedClients;
	notifiedClients.push_back(this->getFd());

	
	// OUTER LOOP: Iterate through the Client's map of channels
	std::map<std::string, Channel*>::const_iterator chanIt = _channels.begin();

	for (; chanIt != _channels.end(); ++chanIt)
	{
		Channel* channel = chanIt->second;

		// Get all Clients in this specific channel
		const std::map<int, Client*>& chanClients = channel->getClients();

		// INNER LOOP: Iterate through the Clients in channel
		std::map<int, Client*>::const_iterator ClientIt = chanClients.begin();
		for (; chanIt != _channels.end(); ++chanIt)
		{
			int clientFD = ClientIt->first;
			Client* client = ClientIt->second;

			// If they are NOT in the set, send the message and add them to the set!
			if (std::find(notifiedClients.begin(), notifiedClients.end(), clientFD) == notifiedClients.end())
			{
				client->sendMessage(msg);
				notifiedClients.push_back(clientFD);
			}

		}
	}
}
