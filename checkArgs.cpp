#include "ircserv.hpp"

// Check if the port is not already in use by another service on the machine and allowed by the firewall. -> Throw an exception otherwise.

void	surveyForHelp(void)
{
	std::string	answer;

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
		displayLaunchExemple();
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
