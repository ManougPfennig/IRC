#include "ircserv.hpp"

// Checks if the word after the PRIVMSG command is a channel or a user
int	isChannelNameAChannel(t_server *serv, std::string channelName) {

	// Loop on all existing channel
	for (std::map<std::string, Channel>::const_iterator it = serv->channelMap.begin(); it != serv->channelMap.end(); it++) {
		// If the specified name is a channel name, return true
		if (it->first == channelName)
			return 1;
	}

	// If the channel name is not a channel, return false
	return 0;
}

// Broadcast a private message to the specified user, if he exists
void	sendPrivateMessage(t_server *serv, std::string receiverName, int clientFd, std::string arg) {

	// Store the receiverFd
	int	receiverFd = gC(serv, receiverName);
	
	// Check if that user exists
	if (receiverFd == -1) {
		sendMsg(clientFd, "Error: User not found.\n");
		return ;
	}

	// Store the username and the nickname of the sender, then the nickname of the receiver
	std::string	senderU = gC(serv, clientFd).getUsername();
	std::string	senderN = gC(serv, clientFd).getNickname();
	std::string	receiverN = gC(serv, receiverFd).getNickname();

	// Send the private message to the receiver in hexchat format
	std::string	fullmsg = ":" + senderU + "!" + senderN + "@ircserv PRIVMSG " + receiverN + " :" + arg + "\r\n";
	sendMsg(receiverFd, fullmsg.c_str());

	return ;
}
