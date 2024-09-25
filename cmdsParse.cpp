#include "ircserv.hpp"

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
	// else {

	// 	broadcastToChannel(serv, );
	// }
}

void	handleJoin(t_server *serv, int clientFd, std::string channelName, std::string password) {
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		serv->channelMap.insert(std::make_pair(channelName, Channel()));
		if (!password.empty())
			serv->channelMap.find(channelName)->second.setPassword(password);
		std::cout << channelName << " channel created." << std::endl;
		serv->channelMap[channelName].addClientToChannel(clientFd);
	}
	else if (!serv->channelMap.find(channelName)->second.getPassword().empty()) {
		if (serv->channelMap.find(channelName)->second.getPassword() == password) {
			serv->channelMap[channelName].addClientToChannel(clientFd);
			std::cout << clientFd << " joined the channel " << channelName << std::endl;
			std::string	msg = "You joined " + channelName + "\n";
			//
			sendMsg(clientFd, msg.c_str());
		}
		else {
			sendMsg(clientFd, "Wrong password, please try again...\n");
			return ;
		}
	}
	else {
		serv->channelMap[channelName].addClientToChannel(clientFd);
		std::cout << clientFd << " joined the channel " << channelName << std::endl;
		std::string	msg = "You joined " + channelName + "\n";
		sendMsg(clientFd, msg.c_str());
	}

	// Send the JOIN message to tell the client it has joined the channel
	std::string joinMsg = ":" + gC(serv, clientFd).getNickname() + " JOIN #" + channelName + "\r\n";
	std::cout << joinMsg;
	sendMsg(clientFd, joinMsg.c_str());

}

void	broadcastToChannel(t_server *serv, std::string channelName, int senderFd, std::string msg) {
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(senderFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}
	Channel &channel = serv->channelMap[channelName];
	std::vector<int>&clients = channel.getClientsOfChannel();
	std::string	senderU = serv->clientMap.find(senderFd)->second.getUsername();
	std::string	senderN = serv->clientMap.find(senderFd)->second.getNickname();
	std::string	fullmsg = ":" + senderU + "!" + senderN + "@ircserv PRIVMSG #" + channelName + " :" + msg + "\r\n";
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (*it != senderFd)
			sendMsg(*it, fullmsg.c_str());
	}
}

void	handlePart(t_server *serv, int clientFd, std::string &channelName, std::string msg) {
	char	**tab = ft_split(channelName.c_str(), ",");
	for (int i = 0; tab[i]; i++)
		disconnectClientFromChannel(serv, clientFd, channelName, msg);
	freeTab(tab);
	return ;
}

void	broadcastLeaving(t_server *serv, std::string channelName, int senderFd, std::string msg) {
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(senderFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}
	Channel &channel = serv->channelMap[channelName];
	std::vector<int>&clients = channel.getClientsOfChannel();
	std::string	leaverU = serv->clientMap.find(senderFd)->second.getUsername();
	std::string	leaverN = serv->clientMap.find(senderFd)->second.getNickname();
	std::string	fullmsg = ":" + leaverU + "!" + leaverN + "@ircserv PART #" + channelName + " :" + msg + "\r\n";
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		sendMsg(*it, fullmsg.c_str());
	}
}

void	disconnectClientFromChannel(t_server *serv, int clientFd, std::string &channelName, std::string msg) {
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		std::cout << "name:" << channelName << std::endl;
		sendMsg(clientFd, "Error: can't perform this action.\n");
		return ;
	}
	Channel &channel = serv->channelMap[channelName];
	if (!channel.isClientInChannel(clientFd)) {
		std::cout << "9name:" << serv->clientMap.find(clientFd)->second.getUsername() << std::endl;
		sendMsg(clientFd, "[9] Error: can't perform this action.\n");
		return ;
	}
	channel.removeClientFromChannel(clientFd);
	broadcastLeaving(serv, channelName, clientFd, msg);
	// sendMsg(clientFd, "You left this channel.\n");
	std::string partMsg = ":" + gC(serv, clientFd).getNickname() + "!" + gC(serv, clientFd).getUsername() + "@ircserv PART #" + channelName + " :Goodbye\r\n";
	std::cout << partMsg;
	sendMsg(clientFd, partMsg.c_str());
	if (channel.getClientsOfChannel().empty()) {
		serv->channelMap.erase(channelName);
		std::cout << "The channel was empty so it got closed." << std::endl;
	}
}
