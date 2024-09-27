#include "ircserv.hpp"

// Parses the command sent and launch the action needed 
void	cmdsParse(t_server *serv, int clientFd, std::string toParse) {

	// Keeping the command from the input string
	std::string	command = toParse.substr(0, toParse.find_first_of(' '));
	toParse.erase(0, toParse.find_first_of(' ') + 1);

	// Keeping the channel from the input string
	std::string	channelName = toParse.substr(0, std::min(toParse.find_first_of(' '), toParse.find_first_of('\r')));
	toParse.erase(0, toParse.find_first_of(' ') + 1);

	// Keeping the argument from the input string
	std::string	arg = toParse;
	if (arg[0] == ':')
		arg.erase(0, 1);

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
			if (!channelName.empty())
				handleJoin(serv, clientFd, channelName, arg);
			else
				sendMsg(clientFd, "Error: no channel name provided, please try again...\n");
			break ;
		}
		case 5: // PART
		{
			if (!channelName.empty())
				handlePart(serv, clientFd, channelName, arg);
			else
				sendMsg(clientFd, "Error: no channel name provided, please try again...\n");
			break ;
		}
		case 6: // PRIVMSG
		{
			broadcastToChannel(serv, channelName, clientFd, arg);
			break ;
		}
		case 7: // KICK
		{
			break;
		}
	}
	return ;
}
