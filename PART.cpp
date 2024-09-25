#include "ircserv.hpp"

//launch the part command, with the arguments sent (leave one channel or many)
void	handlePart(t_server *serv, int clientFd, std::string &channelName, std::string msg) {
	char	**tab = ft_split(channelName.c_str(), ",#");
	for (int i = 0; tab[i]; i++) {
		std::string	oneChannel = tab[i];
		disconnectClientFromChannel(serv, clientFd, oneChannel, msg);
	}
	freeTab(tab);
	return ;
}

//disconnect a client from a channel and deletes it if he was the last client of the channel, and launch a leaving broadcast
void	disconnectClientFromChannel(t_server *serv, int clientFd, std::string &channelName, std::string msg) {
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		channelName.erase();
		sendMsg(clientFd, "Error: can't perform this action.\n");
		return ;
	}
	Channel &channel = serv->channelMap[channelName];
	if (!channel.isClientInChannel(clientFd)) {
		sendMsg(clientFd, "Error: can't perform this action.\n");
		return ;
	}
	channel.removeClientFromChannel(clientFd);
	broadcastLeaving(serv, channelName, clientFd, msg);
	std::string partMsg = ":" + gC(serv, clientFd).getNickname() + "!" + gC(serv, clientFd).getUsername() + "@ircserv PART #" + channelName + " :Goodbye\r\n";
	std::cout << partMsg;
	sendMsg(clientFd, partMsg.c_str());
	if (channel.getClientsOfChannel().empty()) {
		serv->channelMap.erase(channelName);
		std::cout << "The channel was empty so it got closed." << std::endl;
	}
}
