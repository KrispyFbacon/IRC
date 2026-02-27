#include "Parsing.hpp"

static size_t	skipDelimiters(const std::string *str, size_t i, const std::string &delimiter)
{
	size_t	len = str->length();

	while (i < len && (str->find(delimiter, i) == i || !std::isprint((*str)[i]) || std::isspace((*str)[i])))
		i += (str->find(delimiter, i) == i) ? delimiter.length() : 1;

	return (i);
}

std::vector<std::string>	tokenizeMessage(std::string *str, const std::string delimiter)
{
	std::vector<std::string>	tokens;
	size_t	i = 0;
	size_t	len = str->length();
	size_t	start;

	// Extract command then extract target
	for (size_t j = 0; j < 2; j++)
	{
		i = skipDelimiters(str, i, delimiter);
		start = i;
		while (i < len && str->find(delimiter, i) != i && std::isprint((*str)[i]) && !std::isspace((*str)[i]))
			i++;
		tokens.push_back(str->substr(start, i - start));
	}

	// Extract message
	i = skipDelimiters(str, i, delimiter);
	tokens.push_back(str->substr(i));

	return (tokens);
}

Message	parseMessage()
{
	Message	parsedMessage;
	std::vector<std::string>	words= tokenizeMessage();

	parsedMessage.command = words[0];
	parsedMessage.target = words[1];
	parsedMessage.message = words[2];

	return (parsedMessage);
}
