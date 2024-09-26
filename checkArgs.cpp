#include "ircserv.hpp"

// Will open a prompt to offer help. User can answer 'y' for yes, or anything else for no
void	surveyForHelp(void)
{
	std::cout << YELLOW << "Would you like more info on ports ? y/n\n" << RESET;

	// Opening the prompt
	std::string	answer = getInput();
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

	// Check if the password is valid
	if (strlen(av[2]) == 0)
		std::cout << MAGENTA << "Note: " << RESET << "Connexion will not be password protected" << std::endl;
	else
		for (int i = 0; av[2][i]; i++)
		{
			if (isspace(av[2][i]))
			{
				std::cout << RED << "Error: " << RESET << PASSHELPMESSAGE << std::endl;
				return (ERROR);
			}
		}

	return (ALLGOOD);
}
