#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include<string>
#include <map>

class Client;

class Channel
{
	private:
		std::string	_name;
		std::string	_topic;
		std::map<std::string, Client*>	_clients;

	public:
		Channel(std::string);
		Channel(std::string, const Channel &);
		~Channel();

		void	copyChannelInfo(Channel &, const Channel &);
};

#endif
