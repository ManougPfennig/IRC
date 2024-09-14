#include "ircserv.hpp"

int	main(int ac, char **av)
{
	if (parsing(ac, av) == ERROR)
		return (1);
	std::cout << "all good" << std::endl;
	return (0);
}
