#ifndef PINGCOMMAND_HPP
#define PINGCOMMAND_HPP


class pingCommand
{
	private:
	
	public:
		pingCommand();
		pingCommand(const pingCommand& other);
		~pingCommand();

		pingCommand& operator=(const pingCommand& other);
};

#endif