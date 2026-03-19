#include "ExtraParsing.hpp"

static std::vector<std::string>	splitByComma(const std::string &str)
{
	std::vector<std::string>	result;
	size_t						start = 0;
	size_t						pos;

	while ((pos = str.find(',', start)) != std::string::npos)
	{
		if (pos > start)
			result.push_back(str.substr(start, pos - start));
		start = pos + 1;
	}
	if (start < str.size())
		result.push_back(str.substr(start));

	return (result);
}

// Parse a raw JOIN line into a JoinMessage.
//
// Input examples:
//   "JOIN #chan1,#chan2,#chan3 pass1,pass2,pass3"
//   "JOIN #chan1,#chan2,#chan3"
//   "JOIN #chan1"
//
// Output:
//   channels[0] = "JOIN #chan1"    keys[0] = "PASS pass1"
//   channels[1] = "JOIN #chan2"    keys[1] = "PASS pass2"
//   channels[2] = "JOIN #chan3"    keys[2] = "PASS pass3"
//
// Keys are matched positionally. Channels with no matching key get "PASS ".

JoinMessage	parseJoinMessage(const std::string &raw)
{
	JoinMessage	result;

	Message	msg = parseMessage(raw);

	if (msg.command != "JOIN" || msg.params.empty())
		return (result);

	std::vector<std::string>	channels = splitByComma(msg.params[0]);
	std::vector<std::string>	keys;

	if (msg.params.size() > 1)
		keys = splitByComma(msg.params[1]);

	for (size_t i = 0; i < channels.size(); ++i)
	{
		result.channels.push_back("JOIN " + channels[i]);

		if (i < keys.size())
			result.keys.push_back("PASS " + keys[i]);
		else
			result.keys.push_back("PASS ");
	}

	return (result);
}