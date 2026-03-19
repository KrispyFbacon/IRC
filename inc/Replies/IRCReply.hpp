#ifndef IRCREPLY_HPP
#define IRCREPLY_HPP

#include "IRCCodes.hpp"

class Client;

void sendError(Client& client, const std::string& code, const std::string& msg);
void sendReply(Client& client, const std::string& code, const std::string& msg);

#endif