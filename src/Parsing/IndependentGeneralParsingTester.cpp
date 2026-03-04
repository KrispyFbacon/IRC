// // === HOW TO USE ===
// // Copy updated GeneralParser.hpp and GeneralParser.cpp into this file before testing
// // Resolve all dependencies before testing because this file isn't connected to the rest of the program
// //
// // Follow the commands using the linux terminal:
// // cd [IRC repository folder]/src/Parsing
// // c++ -Wall -Wextra -Werror -std=c++98 GeneralParsingTester.cpp
// // valgrind --leak-check=full --show-leak-kinds=all ./a.out
// //
// // Don't forget to DELETE "a.out" file after testing


// // ----------------- Parser code -----------------

// #include <string>
// #include <vector>

// struct Message
// {
// 	std::string	command;
// 	std::string	target;
// 	std::string	message;
// };

// static size_t	skipDelimiters(const std::string *str, size_t i, const std::string &delimiter)
// {
// 	size_t	len = str->length();

// 	while (i < len && (str->find(delimiter, i) == i || !std::isprint((*str)[i]) || std::isspace((*str)[i])))
// 		i += (str->find(delimiter, i) == i) ? delimiter.length() : 1;

// 	return (i);
// }

// std::vector<std::string>	tokenizeMessage(const std::string *str, const std::string delimiter)
// {
// 	std::vector<std::string>	tokens;
// 	size_t	i = 0;
// 	size_t	len = str->length();
// 	size_t	start;

// 	for (size_t j = 0; j < 2; j++)
// 	{
// 		i = skipDelimiters(str, i, delimiter);
// 		start = i;
// 		while (i < len && str->find(delimiter, i) != i && std::isprint((*str)[i]) && !std::isspace((*str)[i]))
// 			i++;
// 		tokens.push_back(str->substr(start, i - start));
// 	}

// 	i = skipDelimiters(str, i, delimiter);
// 	tokens.push_back(str->substr(i));

// 	return (tokens);
// }

// Message	parseMessage(const std::string str)
// {
// 	Message	parsedMessage;
// 	std::vector<std::string>	words= tokenizeMessage(&str, " ");

// 	parsedMessage.command = words[0];
// 	parsedMessage.target = words[1];
// 	parsedMessage.message = words[2];

// 	return (parsedMessage);
// }


// // ----------------- Tester -----------------
// #include <iomanip>  // for std::hex
// #include <sstream>
// #include <iostream>

// // Print string showing non-printables
// std::string visualize(const std::string& str)
// {
//     std::ostringstream oss;

//     for (size_t i = 0; i < str.size(); ++i)
//     {
//         unsigned char c = str[i];

//         if (std::isprint(c))
//             oss << c;
//         else
//             oss << "\\x" << std::hex << std::uppercase
//                 << std::setw(2) << std::setfill('0')
//                 << static_cast<int>(c);
//     }
//     return oss.str();
// }

// void runTest(const std::string& input)
// {
//     std::cout << "Raw Input   : " << visualize(input) << "\n";

//     Message msg = parseMessage(input);

//     std::cout << "Command     : [" << visualize(msg.command) << "]\n";
//     std::cout << "Target      : [" << visualize(msg.target)  << "]\n";
//     std::cout << "Message     : [" << visualize(msg.message) << "]\n";
//     std::cout << "--------------------------------------\n";
// }

// int	main()
// {
// 	std::vector<std::string>	testCases;

// 	testCases.push_back("PRIVMSG user Hello");
// 	testCases.push_back("   PRIVMSG   user   Hello   ");
// 	testCases.push_back("\tPRIVMSG\tuser\tHello");
// 	testCases.push_back("PRIVMSG user Hello\n");
// 	testCases.push_back("PRIVMSG user Hello\r\n");
// 	testCases.push_back("PRIVMSG user Hello\vWorld");
// 	testCases.push_back("PRIVMSG user Hello\fWorld");
// 	testCases.push_back("PRIVMSG user Hello\x01\x02");
// 	testCases.push_back("\x01\x02PRIVMSG user Hello");
// 	testCases.push_back("   ");
// 	testCases.push_back("");
// 	testCases.push_back("ONLYCOMMAND");
// 	testCases.push_back("CMD target");
// 	testCases.push_back("CMD  target    message   with   weird   spacing");
// 	testCases.push_back("CMD target message\x7F");
// 	testCases.push_back("\t\x7FPRIVMSG\t\x7Fuser\tHello\x7F");

// 	for (size_t i = 0; i < testCases.size(); ++i)
// 		runTest(testCases[i]);

// 	return (0);
// }
