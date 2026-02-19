#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include<string>

class Channel
{
private:
	std::string	name;

public:
	Channel(std::string);
	Channel(std::string, const Channel &);
	~Channel();

	void	copyChannelInfo(Channel &, const Channel &);
};

#endif
