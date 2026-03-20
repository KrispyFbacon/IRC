#ifndef PARSING_HPP
# define PARSING_HPP

# include "Utils.hpp"

struct Message
{
	std::string	command;
	std::vector<std::string>	params;
};

struct commaSplit
{
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;
};

Message	parseMessage(const std::string);
commaSplit	splitParse(const Message &);
std::vector<std::string>	splitComma(const std::string &);

#endif
