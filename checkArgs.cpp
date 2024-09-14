#include "ircserv.hpp"

void	surveyForHelp(void)
{
	std::string	answer;

	// Opening a prompt to offer help
	std::cout << YELLOW << "Would you like more info on ports ? y/n\n" << RESET;
	answer = getInput();
	if (answer == "y")
	{
		std::cout << CYAN << PORTHELPMESSAGE << RESET << std::endl;
	}
	return ;
}


int	parsing(int ac, char **av)
{
	// Check for invalid amount of arguments
	if (ac != 3)
	{
		std::cout << YELLOW << "Please start server with a valid argument list :\n";
		std::cout << GREEN << "./ircserv <port> <password>" << RESET << std::endl;
		return (ERROR);
	}

	// Check for errors in the specified port
	if (isStrDigits(av[1]) == false || atol(av[1]) < 1 || atol(av[1]) > 65535)
	{
		std::cout << RED << "Error: " << RESET << "Specified port is invalid\n";
		surveyForHelp();
		return (ERROR);
	}

	// Check if the password is not empty
	if (strlen(av[2]) < 1)
	{
		std::cout << RED << "Error: " << RESET << PASSHELPMESSAGE << std::endl;
		return (ERROR);
	}

	return (ALLGOOD);
}
