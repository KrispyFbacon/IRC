#ifndef IRCREPLY_HPP
#define IRCREPLY_HPP

#include "IRCCodes.hpp"
#include "Client.hpp"

void sendError(Client& client, const std::string& code, const std::string& msg);
void sendReply(Client& client, const std::string& code, const std::string& msg);

#endif