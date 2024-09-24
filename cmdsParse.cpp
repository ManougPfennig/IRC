#include "ircserv.hpp"

void	cmdsParse(t_server *serv, int clientFd, std::string toParse) {
	std::istringstream	iss(toParse);
	std::string			command;
	iss >> command;

	if (command == "JOIN") {
		std::string	channelName;
		std::string	key;
		iss >> channelName;
		iss >> key;
		if (!channelName.empty() && !key.empty())
			handleJoin(serv, clientFd, channelName, key);
		if (!channelName.empty())
			handleJoin(serv, clientFd, channelName, 0);
		else
			sendMsg(clientFd, "Error: No channel name provided, please try again...\n");
	}
	//else
	//	broadcastToChannel(serv, )
}

void	handleJoin(t_server *serv, int clientFd, std::string channelName, std::string password) {
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		serv->channelMap.insert(std::make_pair(channelName, Channel()));
		if (!password.empty())
			serv->channelMap.find(channelName)->second.setPassword(password);
		std::cout << channelName << " channel created." << std::endl;
	}
	else if (!serv->channelMap.find(channelName)->second.getPassword().empty()) {
		if (serv->channelMap.find(channelName)->second.getPassword() == password) {
			serv->channelMap[channelName].addClientToChannel(clientFd);
			std::cout << clientFd << " joined the channel " << channelName << std::endl;
			std::string	msg = "You joined " + channelName + "\n";
			//
			sendMsg(clientFd, msg.c_str());
		}
		else
			sendMsg(clientFd, "Wrong password, please try again...\n");
	}
	else {
		serv->channelMap[channelName].addClientToChannel(clientFd);
		std::cout << clientFd << " joined the channel " << channelName << std::endl;
		std::string	msg = "You joined " + channelName + "\n";
		sendMsg(clientFd, msg.c_str());
	}
}

void	broadcastToChannel(t_server *serv, std::string channelName, int senderFd, std::string msg) {
	//parse RPL received by hexchat
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(senderFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}
	Channel &channel = serv->channelMap[channelName];
	std::vector<int>&clients = channel.getClientsOfChannel();
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (*it != senderFd)
			sendMsg(*it, msg.c_str());
			//send good RPL
	}
}

void	disconnectClientFromChannel(t_server *serv, int clientFd, std::string &channelName) {
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(clientFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}
	Channel &channel = serv->channelMap[channelName];
	if (!channel.isClientInChannel(clientFd)) {
		sendMsg(clientFd, "Error: you're not in this channel.\n");
		return ;
	}
	channel.removeClientFromChannel(clientFd);
	sendMsg(clientFd, "You left this channel.\n");
	if (channel.getClientsOfChannel().empty()) {
		serv->channelMap.erase(channelName);
		std::cout << "The channel was empty so it got closed." << std::endl;
	}
}
