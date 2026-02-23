#include "Client.hpp"
#include "Channel.hpp"

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
	return (_strBuffer);
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

void	Client::setStrBuffer(std::string strBuffer)
{
	_strBuffer = strBuffer;
}

void	Client::setRegistered(bool isRegistered)
{
	_isRegistered = isRegistered;
}

void	Client::setAuthenticated(bool isAuthenticated)
{
	_isAuthenticated = isAuthenticated;
}