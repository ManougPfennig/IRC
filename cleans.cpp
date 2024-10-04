#include "ircserv.hpp"

// Remove the client from all the channels he was still in when disconnecting
void	cleanChannelsFromDisconnectingClients(t_server *serv, int clientFd) {

	Client						&client = gC(serv, clientFd);
	std::vector<std::string>	emptyChannels;

	// Iterating on every channels of the server
	for (std::map<std::string, Channel>::iterator it = serv->channelMap.begin(); it != serv->channelMap.end(); it++) {

		// Client is removed from the channel's client list (removeClientFromChannel will check if he is connected on said channel)
		it->second.removeClientFromChannel(clientFd);

		// Send a departure message to other users in the channel
		broadcastLeaving(serv, it->first, clientFd, "Disconnected");

		// Client is removed from the channel's invite list
		it->second.removeFromInviteList(client.getUsername());

		// Keep a list of channels that are now empty
		if (it->second.getClientsOfChannel().empty()) {
			emptyChannels.push_back(it->first);
		}
	}

	// Closing empty channels
	for (std::vector<std::string>::iterator it = emptyChannels.begin(); it != emptyChannels.end(); it++) {
		std::cout << "erased '" << *it << "' because it is now empty" << std::endl;
		serv->channelMap.erase(*it);
	}

	return ;
}
