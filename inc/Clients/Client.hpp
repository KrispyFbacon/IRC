#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <map>
# include "Utils.hpp"
# include "Channel.hpp"

class Channel;

class Client
{
	private:
		int	_fd;

		std::string	_username;
		std::string	_password;
		std::string	_nickname;

		std::string	_buffer;
		std::string	_outBuffer;

		bool	_isRegistered;
		bool	_isAuthenticated;

		std::map<std::string, Channel*>	_channels;

	public:
		Client(int);
		~Client();

	//getters
		int	getFd() const;

		bool	isRegistered() const;
		bool	isAuthenticated() const;

		std::string	getUsername() const;
		std::string	getPassword() const;
		std::string	getNickname() const;
		std::string	getStrBuffer() const;

		std::string	&getBuffer();
		size_t	getBufferSize() const;

	//setters
		void	setUsername(std::string);
		void	setPassword(std::string);
		void	setNickname(std::string);
		void	setOutBuffer(std::string);

		void	setRegistered(bool);
		void	setAuthenticated(bool);

	//buffer functions
		bool	getNextMessage(std::string &msg);
		void	appendBuffer(const char *data, size_t len);
		void	clearBuffer();

		void	sendMessage(const std::string& msg);

};

#endif
