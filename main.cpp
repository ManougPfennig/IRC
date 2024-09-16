#include "ircserv.hpp"

int	main(int ac, char **av)
{
	// Checks if port and password arguments are valid
	if (parsing(ac, av) == ERROR)
		return (1);
	std::cout << "all good" << std::endl;

	try
	{
		t_server	serv;
		openServer(serv, av[1], av[2]);
		std::cout << "Port: " << serv.port << " Password: " << serv.password << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}
