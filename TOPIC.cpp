#include "ircserv.hpp"

void	TOPIC(t_server *serv, int clientFd, std::string channelName, std::string arg) {

	// Checks if the channel exists
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		channelName.erase();
		sendMsg(clientFd, "Error: can't perform this action.\n");
		return ;
	}

	// Checks if the client is in the specified channel
	Channel &channel = serv->channelMap[channelName];
	if (!channel.isClientInChannel(clientFd)) {
		sendMsg(clientFd, "Error: can't display or change the topic of a channel you're not in.\n");
		return ;
	}

	//if ther's no arguments, just display the channel's topic to the client in the channel
	if (arg.empty()) {
		std::string fullmsg = ":channelTopic!channelTopic@ircserv PRIVMSG #" + channelName + " :" + serv->channelMap.find(channelName)->second.getTopic() + "\r\n";
		sendMsg(clientFd, fullmsg.c_str());
	}
	else {
		//if the topic is changeable by users, change it
		if (serv->channelMap.find(channelName)->second.getTopicSettableByUsers()) {
			serv->channelMap.find(channelName)->second.setTopic(arg);
		}
		else {
			//if not, is the user an operator of this channel ? if yes, change the topic
			if (serv->channelMap.find(channelName)->second.isOperator(clientFd))
				serv->channelMap.find(channelName)->second.setTopic(arg);
			else
				sendMsg(clientFd, "Error: you're not an operator of this channel, can't change channel's topic.\n");
		}
	}
}
