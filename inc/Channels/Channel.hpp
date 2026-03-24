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

		int	_oldestInvited;
		int	_numberOfInvited;

		bool	_inviteOnly;
		bool	_topicLocked;

		std::map<int, Client*>	_clients;
		std::map<int, Client*>	_moderators;
		std::vector<std::string>	_invited;
		std::vector<int>	_joinOrder;

		bool	promoteToModerator(int);

	public:
		Channel(std::string);
		Channel(std::string, const Channel &);
		~Channel();

		const std::map<int, Client*>	&getClients() const;
		const std::map<int, Client*>	&getModerators() const;

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
		void	setUserLimit(const int);

		Client	*getModerator(int);
		bool	addModerator(Client &client);
		bool	removeModerator(const int);
		
		Client	*getClient(const int);
		Client	*getClientByNickname(const std::string);
		bool	addClient(Client &client);
		bool	removeClient(const int);

		std::string	getInvited(const std::string) const;
		bool	addInvited(const std::string);
		bool	removeInvited(const std::string);

		void	broadcast(const std::string &msg, int excludeFd = -1);
};

#endif
