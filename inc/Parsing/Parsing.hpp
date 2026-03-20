#ifndef PARSING_HPP
# define PARSING_HPP

# include "Utils.hpp"

struct Message
{
	std::string	command;
	std::vector<std::string>	params;
};

struct argumentSplit
{
	std::vector<std::string>	targets;
	std::vector<std::string>	keys;
};

Message	parseMessage(const std::string);
argumentSplit	splitParse(const Message &);
std::vector<std::string>	splitComma(const std::string &);

#endif
