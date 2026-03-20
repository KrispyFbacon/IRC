#ifndef EXTRAPARSING_HPP
# define EXTRAPARSING_HPP
 
# include "Parsing.hpp"
 
struct JoinMessage
{
	std::vector<std::string>	channels;	// "JOIN #chan1", "JOIN #chan2", ...
	std::vector<std::string>	keys;		// "PASS pass1",  "PASS pass2",  ...
};
 
JoinMessage	parseJoinMessage(const std::string &);
 
#endif