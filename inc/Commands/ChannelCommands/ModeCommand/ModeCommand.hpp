#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "ACommand.hpp"
#include "ModeICommand.hpp"
#include "ModeKCommand.hpp"
#include "ModeLCommand.hpp"
#include "ModeOCommand.hpp"
#include "ModeTCommand.hpp"

class Server;
class Client;

class ModeCommand : public ACommand
{
	private:
		struct ModeChange
		{
			char		sign;	// '+' or '-'
			char		flag;	// 'i', 't', 'k', 'o', 'l'
			std::string	arg;	// empty if flag takes no argument
		};

		std::vector<ModeChange>	parseModeString(const std::string &modeStr,
												const std::vector<std::string> &args) const;

	public:
		static ACommand *make() { return new ModeCommand(); }

		void execute(Server &server, Client &client, const Message &msg);
};

#endif
