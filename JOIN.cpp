#include "ircserv.hpp"

//launch the join command, creates or join a channel, with a password or not, and broadcast corresponding messages
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
	broadcastJoining(serv, channelName, clientFd);
}
