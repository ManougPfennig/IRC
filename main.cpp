#include "ircserv.hpp"

const char	*cmdType[] = {
	"PASS",
	"NICK",
	"USER",
	"CAP",
	"JOIN",
	"PART",
	"PRIVMSG",
	"KICK",
	"MODE",
	"INVITE",
	"TOPIC",
	NULL,
};

int	main(int ac, char **av)
{
	// Checks if port and password arguments are valid
	if (parsing(ac, av) == ERROR)
		return (1);
	std::cout << "Launching Server..." << std::endl;

	try
	{
		t_server	serv;

		// Opening the server's socket for connexion
		openServer(&serv, av[1], av[2]);

		// Settings up the server to listen for incoming messages and interpreting them
		serverLoop(&serv);

		// Closing the server
		close(serv.serverSocket);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}
