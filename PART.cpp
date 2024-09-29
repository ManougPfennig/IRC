#include "ircserv.hpp"

// Launch the part command, with the arguments sent (to leave one or multiple channels)
void	PART(t_server *serv, int clientFd, std::string channelName, std::string msg)
{
	char	**tab = ft_split(channelName.c_str(), ",#");

	// Disconnecting from each channel in the table
	for (int i = 0; tab[i]; i++) {
		std::string	oneChannel = tab[i];
		disconnectClientFromChannel(serv, clientFd, oneChannel, msg);
	}
	freeTab(tab);
	return ;
}

// Disconnect a client from a channel and broadcasts a leaving message to the other clients in the channel.
// The channel is automatically deleted if left empty.
void	disconnectClientFromChannel(t_server *serv, int clientFd, std::string &channelName, std::string msg)
{
	// Checks if the channel exists
	if (serv->channelMap.find(channelName) == serv->channelMap.end()) {
		channelName.erase();
		sendMsg(clientFd, "Error: can't perform this action.\n");
		return ;
	}

	// Checks if the client is in the specified channel
	Channel &channel = serv->channelMap[channelName];
	if (!channel.isClientInChannel(clientFd)) {
		sendMsg(clientFd, "Error: can't perform this action.\n");
		return ;
	}

	// Remove the client from channel and inform all other clients in the channel
	channel.removeClientFromChannel(clientFd);
	broadcastLeaving(serv, channelName, clientFd, msg);

	// Send a confirmation message to the departing client
	std::string partMsg = ":" + gC(serv, clientFd).getNickname() + "!" + gC(serv, clientFd).getUsername() + "@ircserv PART #" + channelName + " :Goodbye\r\n";
	sendMsg(clientFd, partMsg.c_str());

	// Close the channel if it is now empty
	if (channel.getClientsOfChannel().empty()) {
		serv->channelMap.erase(channelName);
		std::cout << "The channel '" << channelName << "' was empty so it got closed." << std::endl;
	}
	return ;
}
