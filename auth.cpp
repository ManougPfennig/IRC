#include "ircserv.hpp"

// Returns an index corresponding to the cmdType[] array defined in main(), useful for switch cases.
// Returns -1 if the command doesn't exist.
int	whichCommand(std::string cmd)
{
	int i = 0;
	while (cmdType[i])
	{
		if (cmd == cmdType[i])
			return (i);
		i++;
	}
	return (-1);
}

void	registerNewClient(t_server *serv, int key)
{

	char		**toParse = NULL;
	std::string	cmd;

	// Splitting the input into a list of commands
	toParse = ft_split(serv->buffer, "\r\n");

	// Looping through the list of commands to interpret
	for (int i = 0; toParse && toParse[i]; i++)
	{
		cmd = toParse[i];
		// Finding which command has been sent and calling it
		switch (whichCommand(cmd.substr(0, cmd.find_first_of(' '))))
		{
			case 0: // PASS
			{
				PASS(serv, key, cmd.substr(cmd.find_first_of(' ') + 1));
				break;
			}
			case 1: // NICK
			{
				break;
			}
			case 2: // USER
			{
				break;
			}
			case 3: // QUIT
			{
				sendMsg(key, "Disconnecting from server.\n");
				serv->clientMap.erase(key);
				close(key);
				break;
			}
			case -1:
			{
				sendMsg(key, "Invalid command sent.\n");
				break;
			}
		}
	}

	return ;
}
