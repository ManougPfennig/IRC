#include "ircserv.hpp"

// Any port in the range of 1 to 65535 can be used for an IRC server, as long as the port isn’t already in use by another service on the system.
// The ports 6660-6669, 6697, 7000-7005, 8000-8005, 9999 are traditional and commonly used ports for IRC.
// Avoid reserved ports (0-1023): These are reserved for system services like HTTP (80), SSH (22), and others. Any port between 1024 and 65535 is theoretically okay to use.
// Check if the port is not already in use by another service on the machine and allowed by the firewall. -> Throw an exception otherwise.

void	surveyForHelp(void)
{
	std::string	answer;

	std::cout << YELLOW << "Would you like more info ? y/n" << RESET;
	answer = getInput();
}

void	displayLaunchExemple(void)
{
	std::cout << WHITE << "Please start server with valid arguments list :\n";
	std::cout << GREEN << "./ircserv <port> <password>" << RESET << std::endl;
	return ;
}

int	checkAssignedPort(char *port)
{
	if (isStrDigits(port) == false || atol(port) < 1 || atol(port) > 65535)
	{
		std::cout << RED << "Error" << RESET << " : Specified port is invalid\n";
		surveyForHelp();
		return (ERROR);
	}
}

int	parsing(int ac, char **av)
{
	if (ac != 3)
	{
		displayLaunchExemple();
		return (ERROR);
	}
	if (checkAssignedPort(av[1]) == ERROR)
		return (ERROR);
	return (0);
}
