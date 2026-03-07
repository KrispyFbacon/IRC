#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include "Client.hpp"

class Client;

class Channel
{
	private:
		std::string	_name;
		std::string	_topic;

		//TODO std::map<Client*, bool isMod>
		
		// TODO pair? <name/fd, isMod>
		std::map<int, Client*>	_clients;
		std::map<int, Client*>	_moderators;

	public:
		Channel(std::string);
		Channel(std::string, const Channel &);
		~Channel();

		std::string	getChannelName();

		void	copyChannelInfo(Channel &, const Channel &);

		Client	*Channel::getModerator(int clientFd);
		bool	Channel::addModerator(Client *client);
		bool	Channel::removeModerator(Client *client);
		
		bool	Channel::addClient(Client *client);
		bool	Channel::removeClient(Client *client);
};

#endif
