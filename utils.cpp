#include "ircserv.hpp"

// Checks whether the string is made entirely of numeric characters
bool isStrDigits( char *str )
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isdigit(str[i]) == 0)
			return (false);
	}
	return (true);
}

// Displays a prompt to get an input string in the terminal
std::string	getInput( void )
{
	std::string	input;
	while (1)
	{
		input.clear();
		std::getline(std::cin, input);
		// Checks if stdin has been closed and returns empty input (error)
		if (feof(stdin) != 0)
		{
			std::cout << RED << "Closed stdin" << RESET << std::endl;
			return ("");
		}
		// Doesn't check entry if it is empty
		if (input.length() == 0)
			continue;
		else
			break;
	}
	return (input);
}