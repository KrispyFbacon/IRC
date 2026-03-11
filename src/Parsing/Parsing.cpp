#include "Parsing.hpp"

static size_t	skipDelimiters(const std::string *str, size_t i, const std::string &delimiter)
{
	size_t	len = str->length();

	while (i < len && (str->find(delimiter, i) == i))
		i += (str->find(delimiter, i) == i) ? delimiter.length() : 1;

	return (i);
}

std::vector<std::string> tokenizeMessage(const std::string *str, const std::string &delimiter)
{
	std::vector<std::string>	tokens;
	size_t	len = str->length();
	size_t	i = 0;

	while (i < len)
	{
		i = skipDelimiters(str, i, delimiter);
		if (i >= len)
			break;

		if ((*str)[i] == ':' && ((i > 0 && (*str)[i - 1] == ' ') || i == 0))
		{
			std::string	trailing = str->substr(i + 1);
			if (!trailing.empty())
				tokens.push_back(trailing);
			return (tokens);
		}

		size_t start = i;
		while (i < len && str->find(delimiter, i) != i)
			i++;

		if (i > start)
			tokens.push_back(str->substr(start, i - start));
		else
			i++;
	}

	return (tokens);
}

Message	parseMessage(const std::string str)
{
	Message	parsedMessage;

	std::vector<std::string>	words= tokenizeMessage(&str, " ");
	if (words.empty())
		return (parsedMessage);

	parsedMessage.command = toUpper(words[0]);
	for (std::string::size_type i = 1; i < words.size(); i++)
		parsedMessage.params.push_back(words[i]);

	return (parsedMessage);
}
