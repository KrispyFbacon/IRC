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

		bool	_isRegistered;
		bool	_isAuthenticated;
		bool	_isDisconnected;

		std::map<std::string, Channel*>	_channels;

	public:
		Client(int);
		~Client();

	//getters
		int	getFd() const;

		bool	isRegistered() const;
		bool	isAuthenticated() const;
		bool	isDisconnected() const;
		

		std::string	getUsername() const;
		std::string	getPassword() const;
		std::string	getNickname() const;
		std::string	getPrefix() const;

		std::string	&getBuffer();
		size_t	getBufferSize() const;

	//setters
		void	setUsername(std::string);
		void	setPassword(std::string);
		void	setNickname(std::string);

		void	setRegistered(bool);
		void	setAuthenticated(bool);
		void	setDisconnected(bool status);

	// Channel Handler
		void	addChannel(Channel &);
		void	removeChannel(Channel &);
		void	removeChannel(const std::string &);

	//buffer functions
		bool	getNextMessage(std::string &msg);
		void	appendBuffer(const char *data, size_t len);
		void	clearBuffer();

		void	sendMessage(const std::string& msg);

};

#endif
