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

		std::string	getChannelName() const;

		std::string	getTopic() const;
		void	setTopic(const std::string);

		void	copyChannelInfo(Channel &, const Channel &);

		Client	*getModerator(int clientFd);
		bool	addModerator(Client *client);
		bool	removeModerator(Client *client);
		
		bool	addClient(Client *client);
		bool	removeClient(Client *client);
};

#endif
