#include "Parsing.hpp"

static size_t	skipDelimiters(const std::string *str, size_t i, const std::string &delimiter)
{
	size_t	len = str->length();

	while (i < len && (str->find(delimiter, i) == i))
		i += (str->find(delimiter, i) == i) ? delimiter.length() : 1;

	return (i);
}

std::vector<std::string>	tokenizeMessage(const std::string *str, const std::string delimiter)
{
	std::vector<std::string>	tokens;
	size_t	i = 0;
	size_t	len = str->length();
	size_t	start;

	// Extract command then extract target
	for (std::string::size_type i = 0; i < str->length(); ++i)
	{
		if (str[i] == ":")
			break ;
		i = skipDelimiters(str, i, delimiter);
		start = i;
		while (i < len && str->find(delimiter, i) != i)
			i++;
		tokens.push_back(str->substr(start, i - start));
	}

	// Extract message
	i = skipDelimiters(str, i, delimiter);
	tokens.push_back(str->substr(i));

	return (tokens);
}

Message	parseMessage(const std::string str)
{
	Message	parsedMessage;

	std::vector<std::string>	words= tokenizeMessage(&str, " ");
	parsedMessage.command = toUpper(words[0]);
	for (std::string::size_type i = 1; i < words.size(); i++)
		parsedMessage.params.push_back(words[i]);

	return (parsedMessage);
}
