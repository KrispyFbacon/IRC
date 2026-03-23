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
	//TODO

	// Clients that already recieved message
	std::vector<int> notifiedClients;
	notifiedClients.push_back(this->getFd());

	
	// Search through client channel
	// ITERATORES TYPEDEF
	clientIt it = _channels.begin();

	for (; it != _channels.end(); ++it)
	{

	}
	// for (loop throught clients channels)
		// check if same fd -> continue
		// Check if already sent message to that fd
}
