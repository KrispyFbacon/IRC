#ifndef PARSING_HPP
#define PARSING_HPP

#include <string>
#include <vector>
#include "Utils.hpp"

struct Message
{
	std::string	command;
	std::string	target;
	std::string	message;
};

Message	parseMessage(const std::string);

#endif

