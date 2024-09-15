#include "ircserv.hpp"

int	main(int ac, char **av)
{
	// Checks if port and password arguments are valid
	if (parsing(ac, av) == ERROR)
		return (1);
	std::cout << "all good" << std::endl;

	try
	{
		ServerActor	serv;
		openServer(serv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}
