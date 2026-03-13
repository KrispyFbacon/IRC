#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _isRegistered(false), _isAuthenticated(false){}

Client::~Client()
{
	_channels.clear();
}

// Getters

inline int	Client::getFd() const
{
	return (_fd);
}

inline bool	Client::isRegistered() const
{
	return (_isRegistered);
}

inline bool	Client::isAuthenticated() const
{
	return (_isAuthenticated);
}

inline std::string	Client::getUsername() const
{
	return (_username);
}

inline std::string	Client::getPassword() const
{
	return (_password);
}

inline std::string	Client::getNickname() const
{
	return (_nickname);
}

inline std::string	Client::getStrBuffer() const
{
	return (_outBuffer);
}

inline std::string	Client::getPrefix() const
{
	return (_nickname + "!" + _username + "@localhost");
}


// Setters

inline void	Client::setUsername(std::string username)
{
	_username = username;
}

inline void	Client::setPassword(std::string password)
{
	_password = password;
}

inline void	Client::setNickname(std::string nickname)
{
	_nickname = nickname;
}

inline void	Client::setOutBuffer(std::string outBuffer)
{
	_outBuffer = outBuffer;
}

inline void	Client::setRegistered(bool isRegistered)
{
	_isRegistered = isRegistered;
}

inline void	Client::setAuthenticated(bool isAuthenticated)
{
	_isAuthenticated = isAuthenticated;
}

inline std::string	&Client::getBuffer()
{
	return (_buffer);
}

inline size_t	Client::getBufferSize() const
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
