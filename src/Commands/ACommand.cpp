#include "ACommand.hpp"

ACommand::ACommand() {}

ACommand::ACommand(const ACommand& other)
{
	(void)other;
}

ACommand::~ACommand() {}

ACommand& ACommand::operator=(const ACommand& other)
{
	(void)other;
	if (this != &other) {}

	return *this;
}