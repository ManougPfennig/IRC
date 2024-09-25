#include "ircserv.hpp"

//broadcast in hexchat format that a client has join the channel, and open the tab for the joining client
void	broadcastJoining(t_server *serv, std::string channelName, int senderFd) {
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(senderFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}
	Channel &channel = serv->channelMap[channelName];
	std::vector<int>&clients = channel.getClientsOfChannel();
	std::string	senderU = serv->clientMap.find(senderFd)->second.getUsername();
	std::string	senderN = serv->clientMap.find(senderFd)->second.getNickname();
	std::string	msg = ":" + senderU + "!" + senderN + "@ircserv PRIVMSG #" + channelName + " :just joined the channel.\r\n";

	std::string joinerMsg = ":" + gC(serv, senderFd).getNickname() + " JOIN #" + channelName + "\r\n";
	std::cout << joinerMsg;

	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (*it == senderFd)
			sendMsg(senderFd, joinerMsg.c_str());
		else
			sendMsg(*it, msg.c_str());
	}
}

//broadcast in hexchat format a message sent by a client to all other channel members
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

//broadcast in hexchat format that a client is leaving
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
