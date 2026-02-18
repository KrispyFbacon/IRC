#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "../Channel.hpp"
#include <string>
#include <vector>
#include <map>

class Client
{
	private:
		int	_fd;

		std::string	_username;
		std::string	_password;
		std::string	_nickname;
		std::string	_strBuffer;

		bool	_isRegistered;
		bool	_isAuthenticated;

		std::map<std::string, Channel*>	_channels;

	public:
	//orthodox cannonical form
			Client();
			Client(int);
			Client(const Client &);
			Client	&operator=(const Client &);
			~Client();

	//getters
		int	getFd() const;
		bool	isRegistered() const;
		bool	isAuthenticated() const;
		std::string	getUsername() const;
		std::string	getPassword() const;
		std::string	getNickname() const;
		std::string	getStrBuffer() const;

	//setters
		void	setUsername(std::string);
		void	setPassword(std::string);
		void	setNickname(std::string);
		void	setStrBuffer(std::string);

		void	setRegistered(bool);
		void	setAuthenticated(bool);

};

#endif