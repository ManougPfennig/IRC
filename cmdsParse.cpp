#include "ircserv.hpp"

// Parses the command sent and launch the action needed 
void	cmdsParse(t_server *serv, int clientFd, std::string toParse) {

	std::istringstream	iss(toParse);
	std::string			command;
	std::string			channelName;

	iss >> command;
	iss >> channelName;

	// Checking if channelName is preceded by '#' for format, then removing it
	if (!channelName.empty() && channelName[0] != '#') {
		sendMsg(clientFd, "Error: please start the channel name by #...\n");
		return ;
	}
	channelName.erase(0, 1);

	// Switching on the specified command
	switch (whichCommand(command))
	{
		case 4: // JOIN
		{
			std::string	password;
			iss >> password;
			if (!channelName.empty())
				handleJoin(serv, clientFd, channelName, password);
			else
				sendMsg(clientFd, "Error: no channel name provided, please try again...\n");
			break ;
		}
		case 5: // PART
		{
			std::string	msg;
			iss >> msg;
			if (!channelName.empty())
				handlePart(serv, clientFd, channelName, msg);
			else
				sendMsg(clientFd, "Error: no channel name provided, please try again...\n");
			break ;
		}
		case 6: // PRIVMSG
		{
			std::string	msg;
			iss >> msg;
			msg.erase(0,1);
			broadcastToChannel(serv, channelName, clientFd, msg);
			break ;
		}
	}
	return ;
}
