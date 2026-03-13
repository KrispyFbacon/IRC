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
		inline int	getFd() const;

		inline bool	isRegistered() const;
		inline bool	isAuthenticated() const;

		inline std::string	getUsername() const;
		inline std::string	getPassword() const;
		inline std::string	getNickname() const;
		inline std::string	getStrBuffer() const;
		inline std::string	getPrefix() const;

		inline std::string	&getBuffer();
		inline size_t	getBufferSize() const;

	//setters
		inline void	setUsername(std::string);
		inline void	setPassword(std::string);
		inline void	setNickname(std::string);
		inline void	setOutBuffer(std::string);

		inline void	setRegistered(bool);
		inline void	setAuthenticated(bool);

	//buffer functions
		bool	getNextMessage(std::string &msg);
		void	appendBuffer(const char *data, size_t len);
		void	clearBuffer();

		void	sendMessage(const std::string& msg);

};

#endif
