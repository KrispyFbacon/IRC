#ifndef PARSING_HPP
# define PARSING_HPP

# include "Utils.hpp"

struct Message
{
	std::string	command;
	std::vector<std::string>	params;
};

Message	parseMessage(const std::string);
std::vector<std::string>	splitComma(const std::string &);

#endif
