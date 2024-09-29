#include "ircserv.hpp"

// Broadcast in Hexchat format that a client has joined the channel, and opens a dedicated tab for the joining client.
void	broadcastJoining(t_server *serv, std::string channelName, int senderFd) {

	// Checks first if the channel exists
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(senderFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}

	// When a new client joins a channel, a custom message is broadcasted to all other clients on the channel
	Channel				&channel = serv->channelMap[channelName];
	std::vector<int>	&clients = channel.getClientsOfChannel();
	std::string			senderU = gC(serv, senderFd).getUsername();
	std::string			senderN = gC(serv, senderFd).getNickname();


	// A formatted message is first sent as confirmation to the joining client
	std::string	joinerMsg = ":" + senderN + " JOIN #" + channelName + "\r\n";
	sendMsg(senderFd, joinerMsg.c_str());

	// Then a formatted message is broadcasted to all other clients in the channel
	std::string	msg = ":" + senderU + "!" + senderN + "@ircserv PRIVMSG #" + channelName + " :just joined the channel.\r\n";
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (*it != senderFd)
			sendMsg(*it, msg.c_str());
	}
	return ;
}

// Broadcast in Hexchat format a message sent by a channel member to all other channel members
void	broadcastToChannel(t_server *serv, std::string channelName, int senderFd, std::string msg) {

	// Checks if the channel exists
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(senderFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}

	Channel				&channel = serv->channelMap[channelName];
	std::vector<int>	&clients = channel.getClientsOfChannel();
	std::string			senderU = gC(serv, senderFd).getUsername();
	std::string			senderN = gC(serv, senderFd).getNickname();

	// Checks if the client is connected to the channel
	if (channel.isClientInChannel(senderFd) == false) {
		sendMsg(senderFd, "Error: You are not in this channel.\n");
		return ;
	}

	// The message is formatted and broadcasted to all other clients in the channel
	std::string	fullmsg = ":" + senderU + "!" + senderN + "@ircserv PRIVMSG #" + channelName + " :" + msg + "\r\n";
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (*it != senderFd)
			sendMsg(*it, fullmsg.c_str());
	}
	return ;
}

// Broadcast in Hexchat format that a client is leaving
void	broadcastKick(t_server *serv, std::string channelName, int senderFd, int targetFd, std::string msg) {

	// Checks first if the channel exists
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(targetFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}

	Channel				&channel = serv->channelMap[channelName];
	std::vector<int>	&clients = channel.getClientsOfChannel();
	std::string			leaverU = gC(serv, targetFd).getUsername();
	std::string			senderU = gC(serv, senderFd).getUsername();
	std::string			senderN = gC(serv, senderFd).getNickname();

	// :Admin!admin@localhost KICK #lol mapf :You have been removed

	// The message is formatted and broadcasted to all other clients in the channel
	std::string	fullmsg = ":" + senderU + "!" + senderN + "@ircserv KICK #" + channelName + " " + leaverU + " :" + msg + "\r\n";
	std::cout << fullmsg;
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		sendMsg(*it, fullmsg.c_str());
	}
	return ;
}

// Broadcast in Hexchat format that a client is leaving
void	broadcastLeaving(t_server *serv, std::string channelName, int senderFd, std::string msg) {

	// Checks first if the channel exists
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		sendMsg(senderFd, "Error: channel doesn't exist, please try again...\n");
		return ;
	}

	Channel				&channel = serv->channelMap[channelName];
	std::vector<int>	&clients = channel.getClientsOfChannel();
	std::string			leaverU = gC(serv, senderFd).getUsername();
	std::string			leaverN = gC(serv, senderFd).getNickname();

	// The message is formatted and broadcasted to all other clients in the channel
	std::string	fullmsg = ":" + leaverU + "!" + leaverN + "@ircserv PART #" + channelName + " :" + msg + "\r\n";
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		sendMsg(*it, fullmsg.c_str());
	}
	return ;
}
