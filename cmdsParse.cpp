#include "ircserv.hpp"

//parses the command sent and launch the action needed 
void	cmdsParse(t_server *serv, int clientFd, std::string toParse) {
	std::istringstream	iss(toParse);
	std::string			command;
	iss >> command;

	if (command == "JOIN") {
		std::string	channelName;
		std::string	key;
		iss >> channelName;
		if (channelName[0] != '#') {
			sendMsg(clientFd, "Error: please start the channel name by #...\n");
			return ;
		}
		channelName.erase(0,1);
		iss >> key;
		if (!channelName.empty())
			handleJoin(serv, clientFd, channelName, key);
		else
			sendMsg(clientFd, "Error: no channel name provided, please try again...\n");
	}
	else if (command == "PART") {
		std::string	channelName;
		std::string	msg;
		iss >> channelName;
		channelName.erase(0,1);
		iss >> msg;
		if (!channelName.empty())
			handlePart(serv, clientFd, channelName, msg);
		else
			sendMsg(clientFd, "Error: no channel name provided, please try again...\n");
	}
	else if (command == "PRIVMSG") {
		std::string channelName;
		std::string	msg;
		iss >> channelName;
		iss >> msg;
		channelName.erase(0,1);
		msg.erase(0,1);
		broadcastToChannel(serv, channelName, clientFd, msg);
	}
}
