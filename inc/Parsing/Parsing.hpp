#ifndef PARSING_HPP
#define PARSING_HPP

#include "Utils.hpp"

struct Message
{
	std::string	command;
	std::vector<std::string>	params;
};

Message	parseMessage(const std::string);

#endif
