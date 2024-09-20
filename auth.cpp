#include "ircserv.hpp"

int	whichCommand(std::string cmd)
{
	int i = 0;
	while (cmdList[i])
	{
		if (cmd == cmdList[i])
			return (i);
		i++;
	}
	return (-1);
}

std::vector<std::string>	formatCommand(char **cmds)
{
	std::string					tmp;
	std::vector<std::string>	list;

	for (int i = 0; cmds[i]; i++)
	{
		tmp = cmds[i];
		// Checks if the first word of the line is a command, if yes it will add the line to the list of commands
		if (whichCommand(tmp.substr(0, tmp.find_first_of(' '))) >= 0)
			list.push_back(tmp);
		else
			std::cout << "Bad format" << std::endl;
	}
	return (list);
}

void	registerNewClient(t_server *serv, int key)
{

	char						**toParse;
	std::vector<std::string>	cmds;

	toParse = ft_split(serv->buffer, "\r\n");
	cmds = formatCommand(toParse);
	for (auto it = cmds.begin(); it != cmds.end(); it++)
	{
		std::cout << "cmd:-" << *it << "-" << std::endl;
	}
	send(key, "You are now successfully logged in\n", 35, 0);
	// while (toParse.length())
	// {
	// 	// Make a substring containg only the command
	// 	cmd = toParse.substr(0, toParse.find_first_of(' '));
	// 	// Then remove that part from toParse
	// 	toParse = toParse.erase(0, toParse.find_first_of(' ') + 1);

	// 	// Make a substring containing the following word (the command's argument)
	// 	cmdValue = toParse.substr(0, std::min(toParse.find_first_of('\n'), toParse.find_first_of('\t')));

	// 	// Find the command in the list if it exist
	// 	int y = 0;
	// 	while (cmdList[y] != NULL && cmd != cmdList[y])
	// 		y++;

	// 	// Skip whitespaces following the command
	// 	switch (y)
	// 	{
	// 		case 0: // PASS
	// 		{
	// 			if (serv->password == cmdValue)
	// 			{
	// 				std::cout << "\ngot password right" << std::endl;
	// 				serv->clientMap[key].SetPassed(true);
	// 			}
	// 			toParse = toParse.erase(0, std::max(toParse.find_first_of('\n'), toParse.find_first_of('\t')) + 1);
	// 			break;
	// 		}

	// 		case 1: // NICK
	// 		{
	// 			serv->clientMap[key].setNickname(cmdValue);
	// 			std::cout << "\nset nickname to" << serv->clientMap[key].getNickname() << std::endl;
	// 			toParse = toParse.erase(0, std::max(toParse.find_first_of('\n'), toParse.find_first_of('\t')) + 1);
	// 			break;
	// 		}

	// 		case 2: // USER
	// 		{
	// 			serv->clientMap[key].setUsername(cmdValue);
	// 			std::cout << "\nset username to" << serv->clientMap[key].getUsername() << std::endl;
	// 			toParse = toParse.erase(0, std::max(toParse.find_first_of('\n'), toParse.find_first_of('\t')) + 1);
	// 			break;
	// 		}
			
	// 		case 3: // NOT A COMMAND
	// 		{
	// 			toParse = toParse.erase(0, 1);
	// 			break;
	// 		}
	// 	}
	// }

	return ;
}
