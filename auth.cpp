#include "ircserv.hpp"

// Returns an index corresponding to the cmdType[] array defined in main.cpp, useful for switch cases.
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

int	CheckForMissingAuthElements(t_server *serv, int key)
{
	int missingElem = 0;

	// Checks if the client connected using the right password, or send a message
	if (serv->clientMap.find(key)->second.getPassed() == false)
	{
		sendMsg(key, "Send password using 'PASS <password>' :\n");
		missingElem++;
	}
	else
	{
		// Checks if the client set a nickname, or send a message
		if (serv->clientMap.find(key)->second.getNickname().length() == 0)
		{
			sendMsg(key, "Set nickname using 'NICK <nickname>' :\n");
			missingElem++;
		}
		
		// Checks if the client set a username, or send a message
		if (serv->clientMap.find(key)->second.getUsername().length() == 0)
		{
			sendMsg(key, "Set username using 'USER <username>' :\n");
			missingElem++;
		}
	}
	return (missingElem);
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
				NICK(serv, key, cmd.substr(cmd.find_first_of(' ') + 1));
				break;
			}
			case 2: // USER
			{
				USER(serv, key, cmd.substr(cmd.find_first_of(' ') + 1));
				break;
			}
			case -1:
			{
				sendMsg(key, "Invalid command sent.\n");
				break;
			}
		}
	}
	// When the Client has entered all necessary fields, registration is finished.
	if (CheckForMissingAuthElements(serv, key) == 0)
	{
		serv->clientMap.find(key)->second.SetRegistered(true);
		sendMsg(key, "You have registered successfully.\n");
	}
	return ;
}
