#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Utils.hpp"
# include "Client.hpp"
# include "IRCReply.hpp"

class Client;

class Channel
{
	private:
		std::string	_name;
		std::string	_pass;
		std::string	_topic;
		int	_userLimit;

		bool	_inviteOnly;
		bool	_topicLocked;

		std::map<int, Client*>	_clients;
		std::map<int, Client*>	_moderators;
		std::map<int, Client*>	_invited;

	public:
		Channel(std::string);
		Channel(std::string, const Channel &);
		~Channel();

		std::string	getChannelName() const;

		void	copyChannelInfo(Channel &, const Channel &);

		std::string	getTopic() const;
		void	setTopic(const std::string);

		std::string	getPass() const;
		void	setPass(const std::string);

		bool	getInviteOnly() const;
		void	setInviteOnly(bool);

		bool	getTopicLocked() const;
		void	setTopicLocked(bool);

		int		getUserLimit() const;
		void	Channel::setUserLimit(const int);

		Client	*getModerator(int);
		bool	addModerator(Client &client);
		bool	removeModerator(const int);
		
		Client	*getClient(const int);
		Client	*getClientByNickname(const std::string);
		bool	addClient(Client &client);
		bool	removeClient(const int);

		Client	*getInvited(const int);
		Client	*getInvitedByNickname(const std::string);
		bool	addInvited(Client &client);
		bool	removeInvited(const int);

		void	broadcast(const std::string);
};

#endif
