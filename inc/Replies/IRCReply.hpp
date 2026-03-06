#ifndef IRCREPLY_HPP
#define IRCREPLY_HPP

#include <iostream>

class IRCReply
{
	private:
	
	public:
		IRCReply();
		IRCReply(const IRCReply& other);
		~IRCReply();

		IRCReply& operator=(const IRCReply& other);
};

#endif