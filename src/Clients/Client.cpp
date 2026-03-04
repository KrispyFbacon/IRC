#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _isRegistered(false), _isAuthenticated(false){}

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

std::string	Client::getStrBuffer() const
{
	return (_outBuffer);
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

void	Client::setOutBuffer(std::string outBuffer)
{
	_outBuffer = outBuffer;
}

void	Client::setRegistered(bool isRegistered)
{
	_isRegistered = isRegistered;
}

void	Client::setAuthenticated(bool isAuthenticated)
{
	_isAuthenticated = isAuthenticated;
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

void	Client::sendMessage(const std::string& msg)
{
	std::string line = msg + "\r\n";
	send(_fd, line.c_str(), line.size(), 0);
}
